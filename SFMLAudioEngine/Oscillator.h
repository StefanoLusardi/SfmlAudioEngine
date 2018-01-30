#pragma once

#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

class SoundFactory;

class Oscillator : public ISoundSource
{
    friend SoundFactory;

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

//protected:
    Oscillator() { }

private:
    sf::SoundStream *mOscillator;
};