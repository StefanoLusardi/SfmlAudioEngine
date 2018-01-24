#include "AudioManager.h"

AudioManager::AudioManager() : mAudioEngine(new AudioEngine, [](AudioEngine *audioEngine) {delete audioEngine; })
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::Update(const float updateTime) const
{
    mAudioEngine->Update(updateTime);
}

void AudioManager::RegisterSound(const SoundId id, const SoundDescription& description) const
{
    mAudioEngine->mSounds[id] = description;
}

void AudioManager::UnregisterSound(const SoundId id) const
{
    const auto sound = mAudioEngine->mSounds.find(id);
    if (sound != mAudioEngine->mSounds.end())
        mAudioEngine->mSounds.erase(sound);
}

void AudioManager::LoadSound(const SoundId id)
{
    mAudioEngine->LoadSound(id);    
}

void AudioManager::PlaySound(const SoundId id, const Vector3d& position, float volume)
{
    const auto soundId = mAudioEngine->mNextSoundId++;
    const auto sound = mAudioEngine->mSounds.find(id);
    if (sound != mAudioEngine->mSounds.end())
        return;

    mAudioEngine->mInstances[soundId] = SoundInstance(id, sound->second, position, volume);
}

void AudioManager::StopSound(const SoundId id, const float fadeoutMilliseconds)
{
    const auto sound = mAudioEngine->mInstances.find(id);
    if (sound != mAudioEngine->mInstances.end())
        return;

    if (fadeoutMilliseconds <= 0.0f)
        sound->second.Stop();
    else
    {
        sound->second.SetStopRequest(true);
        sound->second.StartFadeout(fadeoutMilliseconds, 0.0f);
    }
}
