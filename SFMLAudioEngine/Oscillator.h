#pragma once

#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

class SoundFactory;

class Oscillator : public ISoundSource
{
    friend class SoundFactory;

public:
    ~Oscillator() override
    {
        delete mOscillator;
    }

    void Play() override
    {
        mOscillator->play();
    }

    void Stop() override
    {
        mOscillator->stop();
    }

    void Pause() override
    {
        mOscillator->pause();
    }

private:
    Oscillator() :mOscillator{nullptr}
    { }
    
    sf::SoundStream *mOscillator;
};