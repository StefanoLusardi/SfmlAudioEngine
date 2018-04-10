#pragma once
#include <SFML/Audio/SoundSource.hpp>

#pragma warning( disable : 4244) 

class ISoundSource : public sf::SoundSource
{
public:
	virtual ~ISoundSource() { }

    virtual void Play()  = 0;
    virtual void Stop()  = 0;
    virtual void Pause() = 0;

    virtual void SetLoop(const bool isLoop)     = 0;
    virtual void SetPitch(const double pitch)   = 0;
    virtual void SetVolume(const double volume) = 0;
    virtual void SetPosition(const AudioUtils::Vector3d& position){}

    virtual double GetPitch()  = 0;
    virtual double GetVolume() = 0;
	virtual AudioUtils::Vector3d GetPosition() { return AudioUtils::Vector3d(); }
	
	virtual bool IsMono() = 0;
	virtual bool IsSourcePlaying() = 0;

protected:
    ISoundSource() { }
};