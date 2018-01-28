#include "AudioManager.h"

AudioManager::AudioManager() 
: mAudioEngine(new AudioEngine, [](AudioEngine *audioEngine) {delete audioEngine; })
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Update(const double updateTime) const
{
    mAudioEngine->Update(updateTime);
}

//void AudioManager::RegisterSound(const SoundId id, const SoundDescription& description) const
//{
    //mAudioEngine->mSounds[id] = description;
//}

//void AudioManager::UnregisterSound(const SoundId id) const
//{
    //const auto sound = mAudioEngine->mSounds.find(id);
    //if (sound != mAudioEngine->mSounds.end())
    //    mAudioEngine->mSounds.erase(sound);
//}

void AudioManager::LoadSound(const SoundId id) const
{
    mAudioEngine->LoadSound(id);    
}

void AudioManager::UnloadSound(const SoundId id) const
{
    mAudioEngine->UnloadSound(id);
}

void AudioManager::PlaySound(const SoundId id, const Vector3d& position, const double volume) const
{
    mAudioEngine->PlaySound(id, position, volume);
}

void AudioManager::StopSound(const SoundId id, const double fadeoutMilliseconds) const
{
    mAudioEngine->StopSound(id, fadeoutMilliseconds);
}

void AudioManager::PauseSound(const SoundId id) const
{
    mAudioEngine->PauseSound(id);
}
