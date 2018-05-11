#pragma once

#include "Utils.h"
#include "AudioEngine.h"
#include "SoundDescription.h"
   
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <ratio>
#include <chrono>

class PolyphonyManager;

class AudioManager final
{
public:
    explicit AudioManager(Mixer& mixer, PolyphonyManager& polyphonyManager);
	~AudioManager() = default;
	AudioManager(const AudioManager& other) = delete;
	AudioManager(AudioManager&& other) = delete;
	AudioManager& operator=(const AudioManager& other) = delete;
	AudioManager& operator=(AudioManager&& other) = delete;
	
    void RegisterSounds(const std::vector<SoundDescription>& descriptions) const;
    void RegisterSound(const SoundDescription& description) const;
    void UnregisterSound(const std::string& soundName) const;
    void UnregisterSounds() const;

    void LoadSound(const std::string& soundName) const;
    void UnloadSound(const std::string& soundName) const;

    void PlaySound(const std::string& soundName, const Vector3D& position, const double volume, const double fadeinMilliseconds) const;
    void StopSound(const std::string& soundName, const double fadeoutMilliseconds) const;
    void PauseSound(const std::string& soundName, const double fadeoutMilliseconds) const;

    void Update(const std::chrono::duration<double, std::milli> updateTime) const;

    void SetSoundVolume(const std::string& soundName, const double volume, const bool isIncremental) const;
    void SetSoundPitch(const std::string& soundName, const double pitch, const bool isIncremental) const;
	void SetSoundPosition(const std::string& soundName, const Vector3D& position, const bool isIncremental) const;

	void StopAllSounds() const;
	void PauseAllSounds() const;
	void ResumeAllSounds() const;
	void SetGlobalVolume(const double globalVolume) const;

	void SetListenerPosition(const Vector3D& vPosition) const;
	void SetListenerDirection(const Vector3D& vDirection) const;
	void SetListenerUpVector(const Vector3D& vUp) const;

	void SetGroupVolume(const std::string& groupName, const double volume) const;

private:
    std::unique_ptr<AudioEngine, std::function<void(AudioEngine*)>> mAudioEngine;
};

