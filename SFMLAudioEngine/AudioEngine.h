#pragma once
#include <map>
#include "SoundInstance.h"
#include "SoundDescription.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();
    void LoadSound(const SoundId id);
    void UnloadSound(const SoundId id);
    void CreateSoundObject(const SoundDescription description);
    void Update(float updateTime);
    void PlaySoundObject();

    //private:
    SoundId mNextSoundId;
    std::map<const SoundId, SoundDescription> mSounds;
    std::map<const SoundId, SoundInstance> mInstances;
};

