#include "AudioEngine.h"
#include "SoundFactory.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <SFML/Audio/Listener.hpp>

AudioEngine::AudioEngine(Mixer& mixer, PolyphonyManager& polyphonyManager)
: mNextInstanceId{ 1 }, mMixer{ mixer }, mPolyphonyManager{ polyphonyManager }
{
    SoundFactory::Initialize();
	sf::Listener::setPosition(0.f, 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
}

bool AudioEngine::IsLoaded(const std::string& soundName)
{
	return FindSound(soundName) != mSounds.end();
}

bool AudioEngine::IsInstanciated(const std::string& soundName)
{
	return FindInstance(soundName) != mInstances.end();
}

/**
 * Helper function to retrieve a pair of mSounds map given a sound name
 */
auto AudioEngine::FindSound(const std::string& soundName) -> decltype(mSounds)::iterator
{
	return std::find_if(mSounds.begin(), mSounds.end(),
        [&soundName](const auto& sound) {return soundName == sound.first.mSoundName; });
}

/**
* Helper function to retrieve a pair of mInstances map given a sound name
*/
auto AudioEngine::FindInstance(const std::string& soundName) -> decltype(mInstances)::iterator
{
    return std::find_if(mInstances.begin(), mInstances.end(),
        [&soundName](const auto& sound) {return soundName == sound.second->GetName(); });
}

void AudioEngine::RegisterSounds(const std::vector<SoundDescription>& descriptions)
{
    for (const auto& description : descriptions)
        RegisterSound(description);
}

void AudioEngine::RegisterSound(const SoundDescription& description)
{
    // Here use standard map::find since we are searching for a description (SoundDescription), not a soundName (std::string)
    const auto descriptionIt = mSounds.find(description);
    if (descriptionIt != mSounds.end()) 
        return;

    //mSounds.emplace(std::make_pair(description, std::make_shared<ISoundSource>()));
    mSounds.emplace(std::make_pair(description, nullptr));
}

void AudioEngine::UnregisterSound(const std::string& soundName)
{
    const auto sound = FindSound(soundName);
    mSounds.erase(sound);
}

void AudioEngine::UnregisterSound(const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound)
{
    // Merge this function inside UnregisterSounds
    // First release the sound source, then erase it from the map.
    mSounds.erase(sound);
}

void AudioEngine::UnregisterSounds()
{
    std::for_each(mSounds.begin(), mSounds.end(), [this](const auto& sound) {mSounds.erase(sound.first); });
}

void AudioEngine::LoadSound(const std::string& soundName)
{
    // Check if a sound source is already loaded in the mSoundSources map
    // if so return, otherwise create a sound source to be later used by a sound instance

    const auto sound = FindSound(soundName);
    if (sound == mSounds.end())
        return;

    mSounds[sound->first] = SoundFactory::Create(sound->first);
}

void AudioEngine::UnloadSound(const std::string& soundName)
{
    const auto sound = FindSound(soundName);
    if (sound == mSounds.end())
        return;

    // Call UnregisterSound()
    // First release the sound resource, then erase it from the map.
    //sound->second.ReleaseSound();
    mSounds.erase(sound);
}

void AudioEngine::Update(const std::chrono::duration<double, std::milli> updateTime)
{
    // Update instances at each game tick, then retrieve the stopped ones.
    std::vector<std::map<SoundId, std::unique_ptr<SoundInstance>>::iterator> stoppedInstances;
    for (auto it = mInstances.begin(), itEnd = mInstances.end(); it != itEnd; ++it)
    {
        it->second->Update(updateTime);
        if (it->second->GetState() == SoundInstance::SoundState::STOPPED)
            stoppedInstances.push_back(it);
    }

    // Delete stopped instances
    for (auto& it : stoppedInstances)
		mInstances.erase(it);
}

SoundId AudioEngine::PlaySound(const std::string& soundName, const Vector3d& position, const double volume, const double fadeinMilliseconds)
{
	// Check that the sound is loaded
    const auto sound = FindSound(soundName);
    if (sound == mSounds.end())
        return -1;

	// Resume a paused Sound Instance
	const auto pausedInstance = FindInstance(soundName);
	if (pausedInstance->second->GetState() == SoundInstance::SoundState::PAUSED && 
		pausedInstance != mInstances.end())
	{
		pausedInstance->second->SetPauseRequest(false);

		if (fadeinMilliseconds > 0.0f)
			pausedInstance->second->StartFade(fadeinMilliseconds, 1.0f);

		return mNextInstanceId;
	}
	
	// Create a new Sound Instance and track it into Polyphony Manager
	auto removedInstanceId{ 0 };
	if (mPolyphonyManager.Push(sound->first.mMixerGroup, mNextInstanceId, std::move(removedInstanceId)))
	{
		mInstances[mNextInstanceId] = std::make_unique<SoundInstance>(*this, sound, position, volume);

		if (fadeinMilliseconds > 0.0f)
			mInstances[mNextInstanceId]->StartFade(fadeinMilliseconds, 1.0f);

		// If pushing a new instance in the Polyphony Manager an old instance is removed we need to stop it
		if (removedInstanceId)
		{
			const auto fadeoutMilliseconds { 500 }; // Default fadeout time for instances removed from Polyphony Manager
			mInstances[removedInstanceId]->StartFade(fadeoutMilliseconds, 0.0f);
			mInstances[removedInstanceId]->SetStopRequest(true);
		}

		mNextInstanceId++;
	}

    return mNextInstanceId;
}

void AudioEngine::StopSound(const std::string& soundName, const double fadeoutMilliseconds)
{
    const auto sound = FindInstance(soundName);
    if (sound == mInstances.end())
        return;

    if (fadeoutMilliseconds > 0.0f)
        sound->second->StartFade(fadeoutMilliseconds, 0.0f);

    sound->second->SetStopRequest(true);

	// Remove stopped Sound Instance from Polyphony Manager
	mPolyphonyManager.Pop(sound->second->GetSoundDescription().mMixerGroup);
}

void AudioEngine::PauseSound(const std::string& soundName, const double fadeoutMilliseconds)
{
    const auto sound = FindInstance(soundName);
    if (sound == mInstances.end())
        return;

	if (fadeoutMilliseconds > 0.0f)
		sound->second->StartFade(fadeoutMilliseconds, 0.0f);

    sound->second->SetPauseRequest(true);
}

void AudioEngine::StopAllSounds()
{
    for (const auto& sound : mInstances)
        sound.second->SetStopRequest(true);
}

void AudioEngine::PauseAllSounds()
{
	for (const auto& sound : mInstances)
		sound.second->SetPauseRequest(true);
}

void AudioEngine::ResumeAllSounds()
{
	for (const auto& sound : mInstances)
		sound.second->SetStopRequest(true);
}

void AudioEngine::SetSoundVolume(const std::string& soundName, const double volume, const bool isIncremental)
{
    const auto sound = FindInstance(soundName);
    if (sound == mInstances.end())
        return;

    sound->second->SetVolume(volume, isIncremental);
}

void AudioEngine::SetSoundPitch(const std::string& soundName, const double pitch, const bool isIncremental)
{
    const auto sound = FindInstance(soundName);
    if (sound == mInstances.end())
        return;

    sound->second->SetPitch(pitch, isIncremental);
}

void AudioEngine::SetSoundPosition(const std::string& soundName, const Vector3d& position, const bool isIncremental)
{
	const auto sound = FindInstance(soundName);
	if (sound == mInstances.end())
		return;

	sound->second->SetPosition(position, isIncremental);
}

void AudioEngine::SetGlobalVolume(const double globalVolume) const
{
	sf::Listener::setGlobalVolume(globalVolume);
}

void AudioEngine::SetListenerPosition(const Vector3d& vPosition) const
{
	sf::Listener::setPosition(vPosition.x, vPosition.y, vPosition.z);
}

void AudioEngine::SetListenerDirection(const Vector3d& vDirection) const
{
	sf::Listener::setDirection(vDirection.x, vDirection.y, vDirection.z);
}

void AudioEngine::SetListenerUpVector(const Vector3d& vUp) const
{
	sf::Listener::setUpVector(vUp.x, vUp.y, vUp.z);
}
