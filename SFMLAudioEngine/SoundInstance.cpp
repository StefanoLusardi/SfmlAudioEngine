#include "SoundInstance.h"
#include "SoundFactory.h"
#include "AudioEngine.h"
#include <cassert>
#include <iostream>

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(const SoundDescription)>> SoundFactory::mCreator = {};

SoundInstance::SoundInstance(AudioEngine& engine
    , const std::map<const SoundDescription, std::shared_ptr<ISoundSource>>::iterator sound
    , const Vector3d& position
    , const double volume)
      : mEngine{engine}
      , mSoundDescription{sound->first}
      , mSoundSource{sound->second}
      , mState{SoundState::INITIALIZE}
      , mPosition{position}
      , mVolume{volume}
      , mStopRequest{false}
{
	mFader = nullptr;
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

void SoundInstance::StartFade(const double fadeoutMilliseconds, const double targetVolume = 0) 
{
	mFader = std::make_unique<AudioFader>(1, 1, 1);
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

void SoundInstance::SetVolume(const double volume, const bool isIncremental) const
{
    // If isIncremental == true, then volume is an absolute value, 
    // otherwise it's a delta to be applied to the current volume.

    if (!isIncremental)
    {
        assert(volume >= 0.0 && volume <= 100.0);
        mSoundSource->SetVolume(volume);
        return;
    }

    // Sum and clip volume in range [0 ; +100]
    auto newVolume = mSoundSource->GetVolume();
    newVolume += volume;

    if (newVolume > 100.0) newVolume = 100.0;
    if (newVolume <   0.0) newVolume = 0.0;

    mSoundSource->SetVolume(newVolume);
}

void SoundInstance::SetPitch(const double pitch, const bool isIncremental) const
{
    if (!isIncremental)
    {
        assert(pitch >= 0.0);
        mSoundSource->SetPitch(pitch);
        return;
    }

    // Sum and clip pitch in range [0.001 ; +inf]
    auto newPitch = mSoundSource->GetPitch();
    newPitch += pitch;

    if (newPitch <= 0.001) newPitch = 0.001;

    mSoundSource->SetPitch(newPitch);
}

void SoundInstance::SetPosition(const Vector3d& position, const bool isIncremental)
{
	if (!isIncremental)
	{
		mSoundSource->SetPosition(position);
		return;
	}

	// Sum and clip pitch in range [0.001 ; +inf]
	auto newPosition = mSoundSource->GetPosition();
	newPosition += position;

	mSoundSource->SetPosition(newPosition);
}

void SoundInstance::Play() const
{
    mSoundSource->Play();
}

void SoundInstance::Stop() const
{
    mSoundSource->Stop();
}

void SoundInstance::Pause() const
{
    mSoundSource->Pause();
}

void SoundInstance::ResetSoundSource()
{
	mSoundSource->setVolume(mSoundDescription.mDefaultVolume);
}

void SoundInstance::Update(const std::chrono::duration<double, std::milli> updateTime)
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
                    return;
                }
                
                mState = SoundState::STOPPING;
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

			if (!mSoundSource->IsSourcePlaying() /*&& !mSoundDescription.mIsLoop*/)
			{
				Stop();
				mState = SoundState::STOPPED;
				return;
			}

			if (mFader && !mFader->IsFinished())
			{
				// Setter here, please!
				mSoundSource->SetVolume(mSoundSource->getVolume() * mFader->GetValue());
				mVolume = mFader->GetValue();

				mFader->Update(updateTime.count());
			}

            break;
        }

        case SoundState::STOPPING:
		{
			if (!mFader || !mSoundSource->IsSourcePlaying())
			{
				Stop();
				mState = SoundState::STOPPED;
				return;
			}
			
			if (mFader->IsFinished())
			{
 				Stop();
				mState = SoundState::STOPPED;
				mSoundSource->SetVolume(mSoundDescription.mDefaultVolume);
				return;
			}	

			// UpdateInstanceParameters();

			// Setter here, please!
			mSoundSource->SetVolume(mSoundSource->getVolume() * mFader->GetValue());
			mVolume = mFader->GetValue();

			mFader->Update(updateTime.count());

            break;
        }

        case SoundState::STOPPED:
        {
            break;
        }
    }
}
