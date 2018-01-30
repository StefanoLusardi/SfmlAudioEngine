#pragma once
#include <map>
#include "SoundInstance.h"
#include "SoundDescription.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine() = default;
    
    void LoadSound(const SoundId id);
    void UnloadSound(const SoundId id);

    void PlaySound(const SoundId id, const Vector3d& position, const double volume);
    void StopSound(const SoundId id, const double fadeoutMilliseconds);
    void PauseSound(const SoundId id);
    
    void CreateSoundSource(const SoundDescription description);
    void Update(const double updateTime);

    // void StopAllSounds();
    // bool IsPlaying(const SoundId id);
    // bool IsLoaded(const SoundId id);

private:
    SoundId mNextInstanceId;
    std::map<const SoundId, SoundDescription> mSounds;
    std::map<const std::string, std::shared_ptr<ISoundSource>> mSoundSources;
    std::map<const SoundId, std::unique_ptr<SoundInstance>> mInstances;
};

