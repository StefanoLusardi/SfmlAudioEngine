#include "AudioFader.h"

AudioFader::AudioFader(const double initialVolume, const double targetVolume, const double deltaTime)
{
    Reset(initialVolume, targetVolume, deltaTime);
}

AudioFader::~AudioFader()
{
}

void AudioFader::Reset(const double initialVolume, const double targetVolume, const double deltaTime)
{
    mInitialVolume = initialVolume;
    mTargetVolume = targetVolume;
    mDeltaVolume = targetVolume - initialVolume;
    mDeltaTime = deltaTime;
}

void AudioFader::Update(const double elapsedTime)
{
    // Linear interpolator: y = ((y1-y0)/(x1-x0))*(x-x0)+y0 (here x0 is always 0)
    // The formula holds both constant and non-constant time increment (no fixed time step)
    mCurrentValue = (mDeltaVolume / mDeltaTime) * elapsedTime + mInitialVolume;
}

double AudioFader::GetValue() const
{
    return mCurrentValue;
}

bool AudioFader::IsFinished() const
{
    return mCurrentValue == mTargetVolume;
}
