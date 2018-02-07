#include "SoundInstance.h"
#include "SoundFactory.h"
#include "AudioEngine.h"

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(std::string)>> SoundFactory::mCreator = {};

SoundInstance::SoundInstance(AudioEngine& engine
    //, const SoundId id
    , const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound
    , const Vector3d& position
    , const double volume)
      : mEngine{engine}
      //, mSoundId{id}
      , mSoundDescription{sound->first}
      , mSoundSource{sound->second}
      , mState{SoundState::INITIALIZE}
      , mPosition{position}
      , mVolume{volume}
      , mStopRequest{false}
{
    mFader = std::make_unique<AudioFader>(1, 1, 1);
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

void SoundInstance::StartFade(const double fadeoutMilliseconds, const double targetVolume = 0) const
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

void SoundInstance::Play() const
{
    mSoundSource->Play();
}

void SoundInstance::Stop() const
{
    mSoundSource->Stop();
}

void SoundInstance::Update(const double updateTime)
{
    // Update instance Finite State Machine logic
    switch(mState)
    {
        // The fallthrough attribute requires C++17
        case SoundState::INITIALIZE: //[[fallthrough]];
        case SoundState::TOPLAY:
        {
            if (mStopRequest)
            {
                mState = SoundState::STOPPING;
                return;
            }

            if (!mEngine.IsLoaded(mSoundDescription.mSoundName))
            {
                mEngine.LoadSound(mSoundDescription.mSoundName);
                mState = SoundState::LOADING;
                return;
            }

            if (mEngine.IsLoaded(mSoundDescription.mSoundName))
            {
                if (mEngine.IsInstanciated(mSoundDescription.mSoundName))
                {
                    // Here we could check for a required fade in.
                    // Or using an override Play(const double fadeInTime)
                    Play();
                    mState = SoundState::PLAYING;
                    
                }
                else
                {
                    mState = SoundState::STOPPING;
                }
            }

            break;
        }

        case SoundState::LOADING:
        {
            if (mEngine.IsLoaded(mSoundDescription.mSoundName))
            {
                mState = SoundState::TOPLAY;
            }

            break;
        }

        case SoundState::PLAYING:
        {
            // UpdateInstanceParameters();
            if (mStopRequest || mState != SoundState::PLAYING)
            {
                mState = SoundState::STOPPING;
                return;
            }

            break;
        }

        case SoundState::STOPPING:
        {
            mFader->Update(updateTime);
            // UpdateInstanceParameters();

            if (mFader->IsFinished())
            {
                Stop();
            }

            if (mState != SoundState::PLAYING)
            {
                mState = SoundState::STOPPED;
                return;
            }

            break;
        }

        case SoundState::STOPPED:
        {
            break;
        }
    }
}
