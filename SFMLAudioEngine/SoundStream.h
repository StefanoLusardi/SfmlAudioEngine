#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>
#include "SoundInstance.h"

class SoundFactory;

class SoundStream : public ISoundSource
{
    friend class SoundFactory;

public:
	~SoundStream() override = default;

	std::shared_ptr<ISoundSource> Clone() const override { return std::shared_ptr<SoundStream>(new SoundStream(this->mSoundDescription)); }

	void Play()		override { mMusic->play(); }
    void Stop()		override { mMusic->stop(); }
    void Pause()	override { mMusic->pause(); }

    void SetLoop(const bool isLoop)				override { mMusic->setLoop(isLoop); }
    void SetPitch(const double pitch)			override { mMusic->setPitch(pitch); }
	void SetVolume(const double volume)			override { mMusic->setVolume(volume); }
	void SetPosition(const Vector3D& position)  override { mMusic->setPosition(position.x, position.y, position.z); }

    double GetPitch()		override { return mMusic->getPitch(); }
	double GetVolume()		override { return mMusic->getVolume(); }
	Vector3D GetPosition()	override { return Vector3D(mMusic->getPosition()); }

	bool IsSourcePlaying() override { return mMusic->getStatus(); }
	bool IsMono() override { return mMusic->getChannelCount() == 1; }

private:
    SoundStream(const SoundDescription& soundDescription) 
	: ISoundSource{soundDescription}
	, mMusic{ std::make_unique<sf::Music>()}
	{		
		mMusic->openFromFile("../AudioSamples/" + soundDescription.mSoundName + ".wav");

		SoundStream::SetLoop(soundDescription.mIsLoop);
		SoundStream::SetPitch(soundDescription.mDefaultPitch);
		SoundStream::SetVolume(soundDescription.mDefaultVolume);

		if (soundDescription.mIs3d && SoundStream::IsMono())
		{
			mMusic->setAttenuation(DistanceToAttenuation(soundDescription.mMaxDistance, soundDescription.mMinDistance));
			mMusic->setMinDistance(soundDescription.mMinDistance);
		}
	}

    std::unique_ptr<sf::Music> mMusic;
};
