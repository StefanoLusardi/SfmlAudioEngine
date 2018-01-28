#pragma once
#include <string>

struct SoundDescription
{
    enum class SoundType {SFX, STREAM, OSC};

    SoundDescription() = default;
    ~SoundDescription() = default;

    std::string mSoundName;
    SoundType mSoundType;
    double mDefaultVolume;
    double mMinDistance;
    double mMaxDistance;
    bool  mIsLoop;
    bool  mIs3d;
};