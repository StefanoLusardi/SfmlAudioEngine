#pragma once
#include "Utils.h"
#include "SoundObject.h"
#include "AudioFader.h"
#include "SoundDescription.h"
#include <memory>

using SoundId = int;
using namespace AudioUtils;

class AudioEngine;

class SoundInstance
{
public:
    enum class SoundState {TOPLAY, PLAYING, STOPPING, STOPPED};

    SoundInstance(const AudioEngine& engine, const SoundId id, const SoundDescription description, const Vector3d& position, const double volume);
    ~SoundInstance();

    void Play();
    void Stop();
    void Update(const double updateTime);

    bool GetStopRequest() const;
    void SetStopRequest(const bool stopRequest);
    void StartFadeout(const double fadeoutMilliseconds, const double targetVolume);

    SoundState GetState() const;

private:
    std::unique_ptr<SoundObject> mSoundObject;
    std::unique_ptr<AudioFader> mFader;
    SoundDescription mSoundDescription;
    SoundId mSoundId;
    SoundState mState;
    Vector3d mPosition;
    double mVolume;
    bool mStopRequest;
    
};

