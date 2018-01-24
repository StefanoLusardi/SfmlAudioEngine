#include "AudioFader.h"



AudioFader::AudioFader()
{
}


AudioFader::~AudioFader()
{
}

void AudioFader::Init(const float initialVolume, const float targetVolume, const float deltaTime)
{
    mInitialVolume = initialVolume;
    mTargetVolume = targetVolume;
    mDeltaVolume = targetVolume - initialVolume;
    mDeltaTime = deltaTime;
}

float AudioFader::GetValue(const float elapsedTime) const
{
    // Linear interpolator: y = ((y1-y0)/(x1-x0))*(x-x0)-y0 (here x0 is always 0)
    // The formula holds both constant and non-constant time increment (no fixed time step)
    return (mDeltaVolume / mDeltaTime) * elapsedTime - mInitialVolume;
}
