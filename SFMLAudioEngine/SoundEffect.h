#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundFactory;

class SoundEffect : public ISoundSource
{
    friend SoundFactory;

public:
	~SoundEffect() override = default;

	std::shared_ptr<ISoundSource> Clone() const override { return std::shared_ptr<SoundEffect>(new SoundEffect(*this)); }

    void Play() override  { mSound.play(); }
    void Stop() override  { mSound.stop(); }
    void Pause() override { mSound.pause(); }

    void SetLoop(const bool isLoop) override     { mSound.setLoop(isLoop); }
    void SetPitch(const double pitch) override   { mSound.setPitch(pitch); }
    void SetVolume(const double volume) override { mSound.setVolume(volume); }
	
	// Spatialization works only for mono sounds
	void SetPosition(const AudioUtils::Vector3D& position) override { mSound.setPosition(position.x, position.y, position.z); }
	AudioUtils::Vector3D GetPosition() override { return AudioUtils::Vector3D(mSound.getPosition()); }

    double GetPitch() override { return mSound.getPitch(); }
    double GetVolume() override { return mSound.getVolume(); }

	bool IsSourcePlaying() override { return mSound.getStatus(); }
	bool IsMono() override { return mSound.getBuffer()->getChannelCount() == 1; }

private:
    SoundEffect(const SoundDescription& soundDescription) 
	: ISoundSource{ soundDescription }
    {
        mBuffer.loadFromFile("../AudioSamples/" + soundDescription.mSoundName + ".wav");
        mSound.setBuffer(mBuffer);

		SoundEffect::SetLoop(soundDescription.mIsLoop);
		SoundEffect::SetPitch(soundDescription.mDefaultPitch);
		SoundEffect::SetVolume(soundDescription.mDefaultVolume);

		if (soundDescription.mIs3d && SoundEffect::IsMono())
		{
			mSound.setAttenuation(DistanceToAttenuation(soundDescription.mMaxDistance, soundDescription.mMinDistance));
			mSound.setMinDistance(soundDescription.mMinDistance);
		}
    }
	
	sf::Sound       mSound;
    sf::SoundBuffer mBuffer;
};
