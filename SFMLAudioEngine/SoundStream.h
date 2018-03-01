#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>
#include "SoundInstance.h"

class SoundFactory;

class SoundStream : public ISoundSource
{
    friend class SoundFactory;

public:
    ~SoundStream() override
    { }

	void Play()  override { mMusic->play(); }
    void Stop()  override { mMusic->stop(); }
    void Pause() override { mMusic->pause(); }

    void SetLoop(const bool isLoop) override     { mMusic->setLoop(isLoop); }
    void SetPitch(const double pitch) override   { mMusic->setPitch(pitch); }
    void SetVolume(const double volume) override { mMusic->setVolume(volume); }

    double GetPitch() override  { return mMusic->getPitch(); }
    double GetVolume() override { return mMusic->getVolume(); }

	bool IsSourcePlaying() override { return mMusic->getStatus(); }

private:
    SoundStream(const SoundDescription soundDescription)
    {
        mMusic = std::make_unique<sf::Music>();
        mMusic->openFromFile("../AudioSamples/" + soundDescription.mSoundName + ".wav");
        //mMusic->setPlayingOffset(sf::seconds(0));
		mMusic->setAttenuation(DistanceToAttenuation(soundDescription.mMaxDistance, soundDescription.mMinDistance));
		mMusic->setMinDistance(soundDescription.mMinDistance);
		mMusic->setLoop(soundDescription.mIsLoop);
		//mMusic->setPitch(soundDescription.mDefaultPitch);
		mMusic->setVolume(soundDescription.mDefaultVolume);
	}	

    SoundStream(sf::Music *sound)
    : mMusic{ sound }
    { }

    std::unique_ptr<sf::Music> mMusic;
};
