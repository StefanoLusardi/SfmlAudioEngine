#pragma once
#include <string>
#include <optional>

struct SoundDescription
{
    enum class SoundType {SFX, STREAM, OSC};
	enum class OscType {SIN, NOISE};
	enum class StealingPolicy { OLDEST, NONE, VOLUME, DISTANCE };

    SoundDescription(
		const std::string&   soundName,
        const SoundType      soundType,
		const std::string&   mixerGroup,
        const double         defaultVolume = 1.0,
		const double         defaultPitch = 1.0,
        const double         minDistance = 1.0,
        const double         maxDistance = 500.0,
        const bool           isLoop = false,
        const bool           is3d = false,		
		const std::optional<OscType> oscType = std::nullopt)
			: mSoundName{ soundName }
			, mSoundType{ soundType }
			, mMixerGroup{ mixerGroup }
            , mDefaultVolume{ defaultVolume }
			, mDefaultPitch{ defaultPitch }
            , mMinDistance{ minDistance }
            , mMaxDistance{ maxDistance }
            , mIsLoop{ isLoop }
            , mIs3d{ is3d }
			, mOscType{oscType}
    { }

	~SoundDescription() = default;
	SoundDescription(const SoundDescription& other) = default;
	SoundDescription(SoundDescription&& other) noexcept = default;
	SoundDescription& operator=(const SoundDescription& other) = delete;
	SoundDescription& operator=(SoundDescription&& other) noexcept = delete;

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
	const std::string mMixerGroup;
    const double mDefaultVolume;
	const double mDefaultPitch;
    const double mMinDistance;
    const double mMaxDistance;
    const bool  mIsLoop;
    const bool  mIs3d;
	const std::optional<OscType> mOscType;
};
