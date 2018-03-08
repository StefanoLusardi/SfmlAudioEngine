#include "AudioFader.h"

AudioFader::AudioFader(const double initialVolume
	, const double targetVolume
	, const double deltaTimeMilliseconds)
{
    Reset(initialVolume, targetVolume, deltaTimeMilliseconds);
}

AudioFader::~AudioFader()
{
}

void AudioFader::Reset(const double initialVolume
	, const double targetVolume
	, const double deltaTimeMilliseconds)
{
	mCurrentTime   = 0;
	mDeltaTime     = deltaTimeMilliseconds;
    mTargetVolume  = targetVolume;
    mInitialVolume = initialVolume;
	mCurrentVolume = initialVolume;
	mStep = (targetVolume - initialVolume) / deltaTimeMilliseconds;
}

void AudioFader::Update(const double elapsedTimeMilliseconds)
{
    // Linear interpolator: y = ((y1-y0)/(x1-x0))*(x-x0)+y0 (here x0 is always 0)
    // The formula holds both constant and non-constant time increment (no fixed time step)
	mCurrentTime += elapsedTimeMilliseconds;
    mCurrentVolume = mStep * mCurrentTime + mInitialVolume;
}

double AudioFader::GetValue() const
{
    return mCurrentVolume;
}

bool AudioFader::IsFinished() const
{
    return mCurrentTime >= mDeltaTime;
}
