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
	  , mFader{nullptr}
      , mState{SoundState::INITIALIZE}
      , mPosition{position}
      , mVolume{volume}
      , mStopRequest{false}
	  , mPauseRequest{false}
{
}

SoundInstance::~SoundInstance()
{
}

void SoundInstance::SetPauseRequest(const bool pauseRequest)
{
	mPauseRequest = pauseRequest;
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
	mFader = std::make_unique<AudioFader>(mVolume, targetVolume, fadeoutMilliseconds);
    //mFader->Reset(mVolume, targetVolume, fadeoutMilliseconds);
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

void SoundInstance::SetPosition(const Vector3d& position, const bool isIncremental) const
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

void SoundInstance::ResetSoundSource() const
{
	mSoundSource->setVolume(mSoundDescription.mDefaultVolume);
	mSoundSource->setPitch(mSoundDescription.mDefaultPitch);
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

			if (mPauseRequest)
			{
				mState = SoundState::PAUSING;
				return;
			}

			// The sound to be played is not loaded --> Load it.
            if (!mEngine.IsLoaded(mSoundDescription.mSoundName))
            {
                mEngine.LoadSound(mSoundDescription.mSoundName);
                mState = SoundState::LOADING;
                return;
            }

            // The sound is already loaded and instanciated --> Play it.
            if (mEngine.IsInstanciated(mSoundDescription.mSoundName))
            {
                Play();
                mState = SoundState::PLAYING;
                return;
            }           

            break;
        }

        case SoundState::LOADING:
        {
			// Loading is finished --> Set ToPlay.
            if (mEngine.IsLoaded(mSoundDescription.mSoundName))
            {
                mState = SoundState::TOPLAY;
            }

            break;
        }

        case SoundState::PLAYING:
		{
			// UpdateInstanceParameters();

			// Stop request is set (or source has chenged its state) --> Set to stopping.
			if (mStopRequest || mState != SoundState::PLAYING)
			{
				mState = SoundState::STOPPING;
				return;
			}

			// Pause request is set --> Set to pausing.
			if (mPauseRequest)
			{
				mState = SoundState::PAUSING;
				return;
			}

			// Source is no longer playing (already stopped) --> Set it to stopped. 
        	// This happens when the source reaches the end of the file before a Stop() is called and the loop is not set.
			if (!mSoundSource->IsSourcePlaying())
			{
				Stop();
				mState = SoundState::STOPPED;
				return;
			}

			// Fade In still in progress --> Update source volume and fader value.
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
			// UpdateInstanceParameters();
			
        	// No Fade Out --> Stop the source.
			if (!mFader || !mSoundSource->IsSourcePlaying())
			{
				Stop();
				mState = SoundState::STOPPED;
				return;
			}
			
			// Fade Out is finished --> Stop the source and reset its volume.
			if (mFader->IsFinished())
			{
 				Stop();
				mState = SoundState::STOPPED;
				mSoundSource->SetVolume(mSoundDescription.mDefaultVolume); // Reset volume to default
				return;
			}	

			// Fade Out still in progress --> Update source volume and fader value.
			{
				// Setter here, please!
				mSoundSource->SetVolume(mSoundSource->getVolume() * mFader->GetValue());
				mVolume = mFader->GetValue();
				mFader->Update(updateTime.count());
				return;
			}

            break;
        }

        case SoundState::STOPPED:
        {
			// Do nothing.
			// This state is needed by the AudioEngine::Update() to clean up unused sound instances
            break;
        }

		case SoundState::PAUSING:
	    {	        
			// UpdateInstanceParameters();

			// No Fade Out --> Pause the source.
			if (!mFader)
			{
				Pause();
				mState = SoundState::PAUSED;
				return;
			}

			// Source is no longer playing (already stopped) --> Set it to stopped. 
			// This happens when the source reaches the end of the file before a Stop() is called and the loop is not set.
			if (!mSoundSource->IsSourcePlaying())
			{
				Stop();
				mState = SoundState::STOPPED;
				return;
			}

			// Fade Out is finished --> Pause the source and keep its properties.
			if (mFader->IsFinished())
			{
				Pause();
				mState = SoundState::PAUSED;
				return;
			}

			// Fade Out still in progress --> Update source volume and fader value.
			{
				// Setter here, please!
				mSoundSource->SetVolume(mSoundSource->getVolume() * mFader->GetValue());
				mVolume = mFader->GetValue();
				mFader->Update(updateTime.count());
				return;
			}

			break;
	    }

		case SoundState::PAUSED:
		{
			// Stop request is set (The sound can be stopped while it's paused) --> Set to stopping.			
			if (mStopRequest)
			{
				mState = SoundState::STOPPING;
				return;
			}

			// Pause request unset --> Resume to play.
			if (!mPauseRequest)
			{
				mState = SoundState::TOPLAY;
				return;
			}
			break;
		}
    }
}
