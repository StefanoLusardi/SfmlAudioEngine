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
    {
    }

    void Play() override
    {
        mSound.play();
    }

    void Stop() override
    {
        mSound.stop();
    }

    void Pause() override
    {
        mSound.pause();
    }

//protected:
    SoundEffect() { }
    SoundEffect(const sf::Sound& sound, const sf::SoundBuffer& buffer)
    : mSound{sound}
    , mBuffer{buffer}
    {
    }

private:
    sf::Sound      mSound;
    sf::SoundBuffer mBuffer;
};
