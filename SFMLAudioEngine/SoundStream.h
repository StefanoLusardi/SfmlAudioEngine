#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

class SoundFactory;

class SoundStream : public ISoundSource
{
    friend class SoundFactory;

public:
    ~SoundStream() override
    {
        //delete mMusic;
    }

    void Play() override
    {
        mMusic->play();
    }

    void Stop() override
    {
        mMusic->stop();
    }

    void Pause() override
    {
        mMusic->pause();
    }

private:
    SoundStream(const std::string soundPath)
    {
        mMusic = std::make_unique<sf::Music>();
        mMusic->openFromFile("../AudioSamples/" + soundPath + ".wav");
        mMusic->setPlayingOffset(sf::seconds(0));
    }

    SoundStream(sf::Music *sound)
    : mMusic{ sound }
    {
        auto x = 0;
    }

    std::unique_ptr<sf::Music> mMusic;
};
