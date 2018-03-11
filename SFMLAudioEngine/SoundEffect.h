#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundFactory;

class SoundEffect : public ISoundSource
{
    friend SoundFactory;

public:
    ~SoundEffect() override
    { }

    void Play() override  { mSound.play(); }
    void Stop() override  { mSound.stop(); }
    void Pause() override { mSound.pause(); }

    void SetLoop(const bool isLoop) override     { mSound.setLoop(isLoop); }
    void SetPitch(const double pitch) override   { mSound.setPitch(pitch); }
    void SetVolume(const double volume) override { mSound.setVolume(volume); }
	
	// Spatialization works only for mono sounds
	void SetPosition(const AudioUtils::Vector3d position) override { mSound.setPosition(position.x, position.y, position.z); }
	AudioUtils::Vector3d GetPosition() override { return AudioUtils::Vector3d(mSound.getPosition()); }

    double GetPitch() override { return mSound.getPitch(); }
    double GetVolume() override { return mSound.getVolume(); }

	bool IsSourcePlaying() override { return mSound.getStatus(); }

private:
    SoundEffect(const SoundDescription soundDescription)
    {
        mBuffer.loadFromFile("../AudioSamples/" + soundDescription.mSoundName + ".wav");
        mSound.setBuffer(mBuffer);
        SoundEffect::SetLoop(soundDescription.mIsLoop);
    }

    SoundEffect(const sf::Sound& sound, const sf::SoundBuffer& buffer)
    : mSound{sound}
    , mBuffer{buffer}
    { }

    sf::Sound       mSound;
    sf::SoundBuffer mBuffer;
};
