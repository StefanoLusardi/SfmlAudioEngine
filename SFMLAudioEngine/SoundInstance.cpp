#include "SoundInstance.h"
#include "SoundFactory.h"

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(std::string)>> SoundFactory::mCreator = {};

SoundInstance::SoundInstance(const AudioEngine* engine
    , const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound
    , const Vector3d& position
    , const double volume)
: mSoundDescription{sound->first}
, mSoundSource{sound->second}
, mState{SoundState::STOPPED}
, mVolume{volume}
, mStopRequest{false}
{
    //mSoundId     = 0; // Set here?
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

const SoundInstance::SoundState SoundInstance::GetState() const
{
    return mState;
}

const std::string SoundInstance::GetName() const
{
    return mSoundDescription.mSoundName;
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
    // Update instance Finite State Machine logic
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
