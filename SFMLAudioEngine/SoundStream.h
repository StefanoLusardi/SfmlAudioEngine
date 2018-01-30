#pragma once
#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

class SoundFactory;

class SoundStream : public ISoundSource
{
    friend SoundFactory;

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

//protected:
    SoundStream() { }
    SoundStream(sf::Music *sound)
    : mMusic{ sound }
    { }

private:
    sf::Music *mMusic;
};
