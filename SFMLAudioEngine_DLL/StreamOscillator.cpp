#include "stdafx.h"

#include "StreamOscillator.h"

StreamOscillator::StreamOscillator()
	: mMaxAmp{16385} //std::numeric_limits<sf::Int16>::max() 
	, mSampleRate{48000}
	, mBufferSize{2048}
	, mFrequency{440.0}
	, mAmplitude{1.0}
	, mPhase{0.0}
	, mPhaseIncrement{TWO_PI * mFrequency / (float)mSampleRate}
	, mBuffer{std::vector<sf::Int16>(mBufferSize, 0)}
{
	const int numChannels = 1;
	initialize(numChannels, mSampleRate);
}

void StreamOscillator::UpdatePhase()
{
	// Increment and keep phase wraped in the [0..2pi] range.
    // Must be called after each new generated sample.
	mPhase += mPhaseIncrement;
	if (mPhase > TWO_PI)
		mPhase -= TWO_PI;
}

void StreamOscillator::onSeek(sf::Time /*timeOffset*/)
{
}
