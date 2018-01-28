#pragma once
#include "Utils.h"
#include <string>
#include <memory>
#include "AudioEngine.h"
#include <functional>
#include "SoundDescription.h"

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    //SoundId RegisterSound(const SoundDescription& description) const;
    //void UnregisterSound(const SoundId id) const;

    void LoadSound(const SoundId id) const;
    void UnloadSound(const SoundId id) const;

    void PlaySound(const SoundId id, const Vector3d& position, const double volume) const;
    void StopSound(const SoundId id, const double fadeoutMilliseconds) const;
    void PauseSound(const SoundId id) const;

    void Update(const double updateTime) const;

    //void StopAllSounds();
    //void SetSoundPosition(const SoundId id);
    //void SetSoundVolume(const SoundId id);

    //void SetListener(const Vector3d& vPosition, const Vector3d& vLook, const Vector3d& vUp);

private:
    std::unique_ptr<AudioEngine, std::function<void(AudioEngine*)>> mAudioEngine;
};

