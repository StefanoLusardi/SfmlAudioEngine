#include "SoundInstance.h"
#include "SoundFactory.h"

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>()>> SoundFactory::mCreator = {};

SoundInstance::SoundInstance(const AudioEngine& engine, const SoundId id, const SoundDescription description, const Vector3d& position, const double volume)
: mSoundId{id}
, mState{SoundState::STOPPED}
, mVolume{volume}
, mStopRequest{false}
{
    //mSoundObject = std::make_unique<SoundObject>(description);
    mSoundSource = SoundFactory::Create(mSoundDescription.mSoundType);
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
    mSoundSource->Play();
}

void SoundInstance::Stop()
{
    mSoundSource->Stop();
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
