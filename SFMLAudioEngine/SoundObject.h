#pragma once
#include "SoundDescription.h"
#include "SoundFactory.h"

class SoundObject
{
public:
    SoundObject(const SoundDescription description);
    ~SoundObject();

    void Play();
    void Stop();

private:
    SoundDescription mDescription;
    sf::SoundSource *mSoundSource;
    sf::SoundBuffer *mSoundBuffer;
};

