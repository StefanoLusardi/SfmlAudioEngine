#include "AudioManager.h"
#include <chrono>
#include <chrono>

AudioManager::AudioManager() 
: mAudioEngine(new AudioEngine, [](AudioEngine *audioEngine) {delete audioEngine; })
{
}

AudioManager::AudioManager(const PolyphonyManager& polyphonyManager)
: mAudioEngine(new AudioEngine(polyphonyManager), [](AudioEngine *audioEngine) {delete audioEngine; })
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::RegisterSounds(const std::vector<SoundDescription>& descriptions) const
{
    mAudioEngine->RegisterSounds(descriptions);
}

void AudioManager::RegisterSound(const SoundDescription& description) const
{
    mAudioEngine->RegisterSound(description);
}

void AudioManager::UnregisterSound(const std::string soundName) const
{
    mAudioEngine->UnregisterSound(soundName);
}

void AudioManager::UnregisterSounds() const
{
    mAudioEngine->UnregisterSounds();
}

void AudioManager::Update(const std::chrono::duration<double, std::milli> updateTime) const
{
    mAudioEngine->Update(updateTime);
}

void AudioManager::SetSoundVolume(const std::string& soundName, const double volume, const bool isIncremental) const
{
    mAudioEngine->SetSoundVolume(soundName, volume, isIncremental);
}

void AudioManager::SetSoundPitch(const std::string& soundName, const double pitch, const bool isIncremental) const
{
    mAudioEngine->SetSoundPitch(soundName, pitch, isIncremental);
}

void AudioManager::SetSoundPosition(const std::string& soundName, const Vector3d position,	const bool isIncremental) const
{
	mAudioEngine->SetSoundPosition(soundName, position, isIncremental);
}

void AudioManager::StopAllSounds() const
{
	mAudioEngine->StopAllSounds();
}

void AudioManager::PauseAllSounds() const
{
	mAudioEngine->PauseAllSounds();
}

void AudioManager::ResumeAllSounds() const
{
	mAudioEngine->ResumeAllSounds();
}

void AudioManager::LoadSound(const std::string soundName) const
{
    mAudioEngine->LoadSound(soundName);    
}

void AudioManager::UnloadSound(const std::string soundName) const
{
    mAudioEngine->UnloadSound(soundName);
}

void AudioManager::PlaySound(const std::string soundName, const Vector3d& position, const double volume, const double fadeinMilliseconds) const
{
    mAudioEngine->PlaySound(soundName, position, volume, fadeinMilliseconds);
}

void AudioManager::StopSound(const std::string soundName, const double fadeoutMilliseconds) const
{
    mAudioEngine->StopSound(soundName, fadeoutMilliseconds);
}

void AudioManager::PauseSound(const std::string soundName, const double fadeoutMilliseconds) const
{
    mAudioEngine->PauseSound(soundName, fadeoutMilliseconds);
}

void AudioManager::SetGlobalVolume(const double globalVolume) const
{
	mAudioEngine->SetGlobalVolume(globalVolume);
}

void AudioManager::SetListenerPosition(const Vector3d& vPosition) const
{
	mAudioEngine->SetListenerPosition(vPosition);
}

void AudioManager::SetListenerDirection(const Vector3d& vDirection) const
{
	mAudioEngine->SetListenerDirection(vDirection);
}

void AudioManager::SetListenerUpVector(const Vector3d& vUp) const
{
	mAudioEngine->SetListenerUpVector(vUp);
}