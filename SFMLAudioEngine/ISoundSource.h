#pragma once
#include <SFML/Audio/SoundSource.hpp>

class ISoundSource : public sf::SoundSource
{
public:
    virtual void Play() = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;

protected:
    ISoundSource(){}
};