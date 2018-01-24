#pragma once
#include <string>

struct SoundDescription
{
    enum class SoundType {SFX, STREAM, OSC};

    SoundDescription();
    ~SoundDescription();

    std::string mSoundName;
    SoundType mSoundType;
    float mDefaultVolume;
    float mMinDistance;
    float mMaxDistance;
    bool  mIsLoop;
    bool  mIs3d;
};

