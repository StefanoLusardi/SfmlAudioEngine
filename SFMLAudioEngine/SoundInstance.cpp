#include "SoundInstance.h"

SoundInstance::SoundInstance()
{
}

SoundInstance::SoundInstance(const SoundId id, const SoundDescription description, const Vector3d& position, float volume):
    mSoundObject(nullptr)
{
}

SoundInstance::~SoundInstance()
{
}

void SoundInstance::SetStopRequest(bool stopRequest)
{
    mStopRequest = stopRequest;
}

bool SoundInstance::GetStopRequest()
{
    return mStopRequest;
}

void SoundInstance::StartFadeout(const float fadeoutMilliseconds, const float targetVolume)
{
    mFader.Init(mVolume, targetVolume, fadeoutMilliseconds);
}

void SoundInstance::Update(float updateTime)
{
}

void SoundInstance::Play()
{
}

void SoundInstance::Stop()
{
}
