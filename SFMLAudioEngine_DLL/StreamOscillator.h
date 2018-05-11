#pragma once

#include <vector>

#include <SFML/Audio/SoundStream.hpp>

#define TWO_PI 6.28318530718

class StreamOscillator : public sf::SoundStream
{
public:
	StreamOscillator();

protected:
    const sf::Int16 mMaxAmp;
    const int mSampleRate;
    const int mBufferSize;

    double mFrequency;
    double mAmplitude;

    double mPhase;
    double mPhaseIncrement;
    std::vector<sf::Int16> mBuffer;

	void UpdatePhase();

	void onSeek(sf::Time /*timeOffset*/) override;
	bool onGetData(Chunk& data) override = 0;
};

