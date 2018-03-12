#include "AudioEngine.h"
#include "SoundFactory.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <SFML/Audio/Listener.hpp>

AudioEngine::AudioEngine()
: mNextInstanceId{ 0 }
{
    SoundFactory::Initialize();
	sf::Listener::setPosition(0.f, 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
}

AudioEngine::AudioEngine(const PolyphonyManager& polyphonyManager)
: mNextInstanceId{ 0 }
{
    SoundFactory::Initialize();
	sf::Listener::setPosition(0.f, 0.f, 0.f);
	sf::Listener::setDirection(0.f, 0.f, -1.f);
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
    mMaxInstances = polyphonyManager.GetMaxInstances();
}

AudioEngine::~AudioEngine()
{
}

bool AudioEngine::IsLoaded(const std::string soundName)
{
    return FindSound(soundName) != mSounds.end();
}

bool AudioEngine::IsInstanciated(const std::string soundName)
{
    return FindInstance(soundName) != mInstances.end();
}

/**
 * Helper function to retrieve a pair of mSounds map given a sound name
 */
std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator 
AudioEngine::FindSound(const std::string soundName)
{    
    return std::find_if(mSounds.begin(), mSounds.end(),
        [soundName](const std::pair<const SoundDescription, std::shared_ptr<ISoundSource>>& sound)
    {return soundName == sound.first.mSoundName; });
}

/**
* Helper function to retrieve a pair of mInstances map given a sound name
*/
std::map<const SoundId, std::unique_ptr<SoundInstance>>::iterator
AudioEngine::FindInstance(const std::string soundName)
{
    return std::find_if(mInstances.begin(), mInstances.end(),
        [soundName](const std::pair<const SoundId, std::unique_ptr<SoundInstance>>& sound)
    {return soundName == sound.second->GetName(); });
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

void AudioEngine::LoadSound(const std::string soundName)
{
    // Check if a sound source is already loaded in the mSoundSources map
    // if so return, otherwise create a sound source to be later used by a sound instance

    const auto sound = FindSound(soundName);
    if (sound == mSounds.end())
        return;

    const auto soundDescription = sound->first;
    mSounds[soundDescription] = SoundFactory::Create(soundDescription);
    //mSounds[soundDescription] = SoundFactory::Create(soundDescription.mSoundType, soundDescription.mSoundName);
}

void AudioEngine::UnloadSound(const std::string soundName)
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

SoundId AudioEngine::PlaySound(const std::string soundName, const Vector3d& position, const double volume, const double fadeinMilliseconds)
{
	// Check that the sound is loaded
    const auto sound = FindSound(soundName);
    if (sound == mSounds.end())
        return -1;

	// Resume a paused Sound Instance
	const auto pausedInstance = FindInstance(soundName);
	if (pausedInstance != mInstances.end() &&
		pausedInstance->second->GetState() == SoundInstance::SoundState::PAUSED)
	{
		pausedInstance->second->SetPauseRequest(false);

		if (fadeinMilliseconds > 0.0f)
			pausedInstance->second->StartFade(fadeinMilliseconds, 1.0f);

		return mNextInstanceId; // unused
	}

	// At the moment there is no control over the active instance counter.
	// In order to limit the polyphony (or just to clamp at a maximum number of active voices),
	// check if the value of mNextInstanceId is below a fixed threshold, maybe set during the initialization of the AudioEngine. 
	// Then we need to keep track of the next available slots after an instance is removed from the mInstances map.
	// So in the future we need a function that makes mNextInstanceId point to the next free slot in the mInstances map.
	const auto instanceId = mNextInstanceId++;

	// Create a new Sound Instance.
    mInstances[instanceId] = std::make_unique<SoundInstance>(*this, sound, position, volume);

	if (fadeinMilliseconds > 0.0f)
		mInstances[instanceId]->StartFade(fadeinMilliseconds, 1.0f);

    return instanceId;
}

void AudioEngine::StopSound(const std::string soundName, const double fadeoutMilliseconds)
{
    const auto sound = FindInstance(soundName);
    if (sound == mInstances.end())
        return;

    if (fadeoutMilliseconds > 0.0f)
        sound->second->StartFade(fadeoutMilliseconds, 0.0f);

    sound->second->SetStopRequest(true);
}

void AudioEngine::PauseSound(const std::string soundName, const double fadeoutMilliseconds)
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
