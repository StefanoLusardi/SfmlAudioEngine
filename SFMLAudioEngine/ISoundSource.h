#pragma once
#include <SFML/Audio/SoundSource.hpp>

class ISoundSource : public sf::SoundSource
{
public:
    virtual void Play()  = 0;
    virtual void Stop()  = 0;
    virtual void Pause() = 0;

    virtual void SetLoop(const bool isLoop)     = 0;
    virtual void SetPitch(const double pitch)   = 0;
    virtual void SetVolume(const double volume) = 0;

    virtual double GetPitch()  = 0;
    virtual double GetVolume() = 0;

    virtual void SetPosition(const AudioUtils::Vector3d position) { setPosition(position.x, position.y, position.z); }
    virtual bool IsSourcePlaying() { return getStatus(); }

protected:
    ISoundSource()
    { }
};