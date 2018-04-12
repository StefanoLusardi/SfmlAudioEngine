#pragma once

#include "Mixer.h"
#include "SoundInstance.h"
#include "SoundDescription.h"
#include "PolyphonyManager.h"

#include <map>
#include <vector>
#include <chrono>

class AudioEngine
{
public:
    explicit AudioEngine(Mixer& mixer, PolyphonyManager& polyphonyManager);
	~AudioEngine() = default;
	AudioEngine(const AudioEngine& other) = delete;
	AudioEngine(AudioEngine&& other) = delete;
	AudioEngine& operator=(const AudioEngine& other) = delete;
	AudioEngine& operator=(AudioEngine&& other) = delete;

    void RegisterSounds(const std::vector<SoundDescription>& descriptions);
    void RegisterSound(const SoundDescription& description);
    void UnregisterSound(const std::string& soundName);
    void UnregisterSound(const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound);
    void UnregisterSounds();

    void LoadSound(const std::string& soundName);
    void UnloadSound(const std::string& soundName);

    SoundId PlaySound(const std::string& soundName, const Vector3d& position, const double volume, const double fadeinMilliseconds);
    void StopSound(const std::string& soundName, const double fadeoutMilliseconds);
    void PauseSound(const std::string& soundName, const double fadeoutMilliseconds);

    void Update(const std::chrono::duration<double, std::milli> updateTime);

    bool IsLoaded(const std::string& soundName);
    bool IsInstanciated(const std::string& soundName);
	auto FindSound(const std::string& soundName) -> std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator;
	auto FindInstance(const std::string& soundName) -> std::map<const SoundId, std::unique_ptr<SoundInstance>>::iterator;

    void SetSoundPitch(const std::string& soundName, const double pitch, const bool isIncremental);
    void SetSoundVolume(const std::string& soundName, const double volume, const bool isIncremental);
	void SetSoundPosition(const std::string& soundName, const Vector3d& position, const bool isIncremental);

    void StopAllSounds();
	void PauseAllSounds();
	void ResumeAllSounds();

	void SetGlobalVolume(const double globalVolume) const;
	void SetListenerPosition(const Vector3d& vector3D) const;
	void SetListenerDirection(const Vector3d& vector3D) const;
	void SetListenerUpVector(const Vector3d& vUp) const;
    

private:
	Mixer& mMixer;
	PolyphonyManager& mPolyphonyManager;

    SoundId mNextInstanceId;
	std::map<const SoundId, std::unique_ptr<SoundInstance>> mInstances;
    std::map<const SoundDescription, std::shared_ptr<ISoundSource>> mSounds;
};

