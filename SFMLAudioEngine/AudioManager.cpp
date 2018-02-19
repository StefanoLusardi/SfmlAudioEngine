#include "AudioManager.h"

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

void AudioManager::Update(const double updateTime) const
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

void AudioManager::LoadSound(const std::string soundName) const
{
    mAudioEngine->LoadSound(soundName);    
}

void AudioManager::UnloadSound(const std::string soundName) const
{
    mAudioEngine->UnloadSound(soundName);
}

void AudioManager::PlaySound(const std::string soundName, const Vector3d& position, const double volume) const
{
    mAudioEngine->PlaySound(soundName, position, volume);
}

void AudioManager::StopSound(const std::string soundName, const double fadeoutMilliseconds) const
{
    mAudioEngine->StopSound(soundName, fadeoutMilliseconds);
}

void AudioManager::PauseSound(const std::string soundName) const
{
    mAudioEngine->PauseSound(soundName);
}
