#include "SoundInstance.h"
#include <memory>

SoundInstance::SoundInstance(const AudioEngine& engine, const SoundId id, const SoundDescription description, const Vector3d& position, const double volume)
: mSoundId{id}
, mState{SoundState::STOPPED}
, mVolume{volume}
, mStopRequest{false}
{
    mSoundObject = std::make_unique<SoundObject>(description);
    mFader       = std::make_unique<AudioFader>(1, 1, 1);
}

SoundInstance::~SoundInstance()
{
}

void SoundInstance::SetStopRequest(const bool stopRequest)
{
    mStopRequest = stopRequest;
}

bool SoundInstance::GetStopRequest() const
{
    return mStopRequest;
}

void SoundInstance::StartFadeout(const double fadeoutMilliseconds, const double targetVolume = 0)
{
    mFader->Reset(mVolume, targetVolume, fadeoutMilliseconds);
}

SoundInstance::SoundState SoundInstance::GetState() const
{
    return mState;
}

void SoundInstance::Play()
{
    mSoundObject->Play();
}

void SoundInstance::Stop()
{
    mSoundObject->Stop();
}

void SoundInstance::Update(const double updateTime)
{
    switch(mState)
    {
        case SoundState::TOPLAY:
        {
            if (mStopRequest)
            {
                mState = SoundState::STOPPING;
                return;
            }
        }

        case SoundState::PLAYING:
        {

        }

        case SoundState::STOPPING:
        {

        }

        case SoundState::STOPPED:
        {

        }
    }
}
