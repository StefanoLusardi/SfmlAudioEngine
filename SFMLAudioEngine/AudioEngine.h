#pragma once
#include <map>
#include "SoundInstance.h"
#include "SoundDescription.h"
#include <vector>
#include "PolyphonyManager.h"

class AudioEngine
{
public:
    AudioEngine();
    explicit AudioEngine(const PolyphonyManager& polyphonyManager);
    ~AudioEngine();

    // Check this C++17 fold function
    //template <typename T, typename ... Ts>
    //bool AudioEngine::RegisterSounds(const T soundsMap, Ts ... descriptions);

    void RegisterSounds(const std::vector<SoundDescription>& descriptions);
    void RegisterSound(const SoundDescription& description);
    void UnregisterSound(const std::string& soundName);
    void UnregisterSound(const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound);
    void UnregisterSounds();

    void LoadSound(const std::string soundName);
    void UnloadSound(const std::string soundName);

    SoundId PlaySound(const std::string soundName, const Vector3d& position, const double volume);
    void StopSound(const std::string soundName, const double fadeoutMilliseconds);
    void PauseSound(const std::string soundName);

    void Update(const double updateTime);

    bool IsLoaded(const std::string soundName);
    bool IsInstanciated(const std::string soundName);
    const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator FindSound(const std::string soundName);
    const std::map<const SoundId, std::unique_ptr<SoundInstance>>::iterator FindInstance(const std::string soundName);
    
    // void StopAllSounds();
    // bool IsPlaying(const SoundId id);
    // bool IsLoaded(const SoundId id);

private:
    int mMaxInstances;
    SoundId mNextInstanceId;

    std::map<const SoundDescription, std::shared_ptr<ISoundSource>> mSounds;
    std::map<const SoundId, std::unique_ptr<SoundInstance>> mInstances;
};

