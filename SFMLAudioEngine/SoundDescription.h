#pragma once
#include <string>

struct SoundDescription
{
    enum class SoundType {SFX, STREAM, OSC};
    
    SoundDescription(
        const std::string soundName,
        const SoundType   soundType,
        const double      defaultVolume = 1.0,
		const double      defaultPitch = 1.0,
        const double      minDistance = 1.0,
        const double      maxDistance = 500.0,
        const bool        isLoop = false,
        const bool        is3d = false)
            : mSoundName(soundName)
            , mSoundType(soundType)
            , mDefaultVolume{ defaultVolume }
			, mDefaultPitch{ defaultPitch }
            , mMinDistance{ minDistance }
            , mMaxDistance{ maxDistance }
            , mIsLoop{ isLoop }
            , mIs3d{ is3d }
    { }

    ~SoundDescription() { }

    bool operator==(const SoundDescription& rhs) const
    {
        return this->mSoundName == rhs.mSoundName;
    }

    bool operator< (const SoundDescription& rhs) const
    {
        return this->mSoundName < rhs.mSoundName;
    }

    const std::string mSoundName;
    const SoundType mSoundType;
    double mDefaultVolume;
	double mDefaultPitch;
    double mMinDistance;
    double mMaxDistance;
    bool  mIsLoop;
    bool  mIs3d;
};