#pragma once
#include "Utils.h"
#include "SoundObject.h"
#include "AudioFader.h"
#include "SoundDescription.h"

using SoundId = int;
using namespace AudioUtils;

class SoundInstance
{
    enum class SoundState {TOPLAY, PLAYING, STOPPING, STOPPED};

public:
    SoundInstance();
    SoundInstance(const SoundId id, const SoundDescription description, const Vector3d& position, float volume);
    ~SoundInstance();
    void Update(float updateTime);
    void Play();
    void Stop();

    void SetStopRequest(bool stopRequest);
    bool GetStopRequest();
    void StartFadeout(const float fadeoutMilliseconds, const float targetVolume);

private:
    SoundId     mSoundId;
    SoundState  mState;
    SoundObject *mSoundObject;
    SoundDescription mSoundDescription;
    bool        mStopRequest;
    float       mVolume;
    Vector3d    mPosition;
    AudioFader  mFader;
    
};

