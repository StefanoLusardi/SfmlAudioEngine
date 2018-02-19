#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

class SoundFactory;

class SoundStream : public ISoundSource
{
    friend class SoundFactory;

public:
    ~SoundStream() override
    { }

    void Play() override  { mMusic->play(); }
    void Stop() override  { mMusic->stop(); }
    void Pause() override { mMusic->pause(); }

    void SetLoop(const bool isLoop) override     { mMusic->setLoop(isLoop); }
    void SetPitch(const double pitch) override   { mMusic->setPitch(pitch); }
    void SetVolume(const double volume) override { mMusic->setVolume(volume); }

    double GetPitch() override  { return mMusic->getPitch(); }
    double GetVolume() override { return mMusic->getVolume(); }

private:
    SoundStream(const SoundDescription soundDescription)
    {
        mMusic = std::make_unique<sf::Music>();
        mMusic->openFromFile("../AudioSamples/" + soundDescription.mSoundName + ".wav");
        //mMusic->setPlayingOffset(sf::seconds(0));
        SoundStream::SetLoop(soundDescription.mIsLoop);
        SoundStream::SetVolume(soundDescription.mDefaultVolume);
    }

    SoundStream(sf::Music *sound)
    : mMusic{ sound }
    { }

    std::unique_ptr<sf::Music> mMusic;
};
