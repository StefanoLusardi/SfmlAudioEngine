#pragma once

#include <memory>
#include <map>

#include "Utils.h"
#include "AudioFader.h"
#include "ISoundSource.h"
#include "SoundDescription.h"

using SoundId = int;
using namespace AudioUtils;

class AudioEngine;

class SoundInstance
{
public:
    enum class SoundState {TOPLAY, PLAYING, STOPPING, STOPPED};

    SoundInstance(const AudioEngine* engine, const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound, const Vector3d& position, const double volume);
    ~SoundInstance();

    void Play();
    void Stop();
    void Update(const double updateTime);

    bool GetStopRequest() const;
    void SetStopRequest(const bool stopRequest);
    void StartFadeout(const double fadeoutMilliseconds, const double targetVolume);

    const SoundState GetState() const;
    const std::string GetName() const;

private:
    SoundDescription mSoundDescription;
    const std::shared_ptr<ISoundSource> mSoundSource;
    std::unique_ptr<AudioFader> mFader;
    SoundState mState;
    Vector3d mPosition;
    double mVolume;
    bool mStopRequest;
    //SoundId mSoundId; // need this? if so pass it in the ctor
};

