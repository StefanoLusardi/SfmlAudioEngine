#include "AudioEngine.h"



AudioEngine::AudioEngine()
{
}

void AudioEngine::LoadSound(const SoundId id)
{
    //if (IsLoaded(id)) return;

    const auto sound = mSounds.find(id);
    if (sound != mSounds.end())
        return;

    mSounds[id] = SoundDescription();
    //CreateSoundObject(sound->second);
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

void AudioEngine::Update(const double updateTime)
{
    // Update instances, then retrieve the stopped ones.
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

void AudioEngine::PlaySound(const SoundId id, const Vector3d& position, const double volume)
{
    const auto instanceId = mNextInstanceId++;
    const auto sound = mSounds.find(id);
    if (sound == mSounds.end())
        return;

    mInstances[instanceId] = std::make_unique<SoundInstance>(*this, id, sound->second, position, volume);
}

void AudioEngine::StopSound(const SoundId id, const double fadeoutMilliseconds)
{
    const auto sound = mInstances.find(id);
    if (sound != mInstances.end())
        return;

    if (fadeoutMilliseconds <= 0.0f)
        sound->second->Stop();
    else
    {
        sound->second->SetStopRequest(true);
        sound->second->StartFadeout(fadeoutMilliseconds, 0.0f);
    }
}

void AudioEngine::PauseSound(const SoundId id)
{
}
