#include "AudioEngine.h"



AudioEngine::AudioEngine()
{
}


AudioEngine::~AudioEngine()
{
}

void AudioEngine::LoadSound(const SoundId id)
{
    //if (SoundIsLoaded(id)) return;

    const auto sound = mSounds.find(id);
    if (sound != mSounds.end())
        return;

    CreateSoundObject(sound->second);
}

void AudioEngine::UnloadSound(const SoundId id)
{
    const auto sound = mSounds.find(id);
    if (sound == mSounds.end())
        return;

    //sound->second.ReleaseSound();
    mSounds.erase(sound);
}

void AudioEngine::CreateSoundObject(const SoundDescription description)
{
}

void AudioEngine::Update(float updateTime)
{
}

void AudioEngine::PlaySoundObject()
{
}
