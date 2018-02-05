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
        delete mMusic;
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
        mMusic = new sf::Music();
        mMusic->openFromFile(soundPath + ".wav");
    }

    SoundStream(sf::Music *sound)
    : mMusic{ sound }
    { }

    sf::Music *mMusic;
};
