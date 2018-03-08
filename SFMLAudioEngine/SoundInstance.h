#pragma once

#include <memory>
#include <map>

#include "Utils.h"
#include "AudioFader.h"
#include "ISoundSource.h"
#include "SoundDescription.h"
#include <chrono>

using SoundId = int;
using namespace AudioUtils;

class AudioEngine;

class SoundInstance
{
public:
    enum class SoundState {INITIALIZE, TOPLAY, PLAYING, STOPPING, STOPPED, LOADING };

    SoundInstance(AudioEngine& engine, const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound, const Vector3d& position, const double volume);
    ~SoundInstance();

    void Play() const;
    void Stop() const;
    void Pause() const;
	void ResetSoundSource();
    void Update(const std::chrono::duration<double, std::milli> updateTime);

    bool GetStopRequest() const;
	void StartFade(const double fadeoutMilliseconds, const double targetVolume);
    void SetStopRequest(const bool stopRequest);
    void StartFade(const double fadeoutMilliseconds, const double targetVolume) const;

    const SoundState GetState() const;
    const std::string GetName() const;
    void SetVolume(const double volume, const bool isIncremental) const;
    void SetPitch(const double pitch, const bool isIncremental) const;
	void SetPosition(const Vector3d& position, const bool isIncremental);

private:
    AudioEngine & mEngine;
    SoundDescription mSoundDescription;
    const std::shared_ptr<ISoundSource> mSoundSource;
    std::unique_ptr<AudioFader> mFader;
    SoundState mState;
    Vector3d mPosition;
    double mVolume;
    bool mStopRequest;
};

