#pragma once
#include "SoundDescription.h"
#include "SoundFactory.h"

class SoundObject
{
public:
    SoundObject(const SoundDescription description);

    ~SoundObject();

private:
    SoundDescription mDescription;
    sf::SoundSource *mSoundSource;
};

