#pragma once

#include "StreamOscillator.h"

class SinOsc : public StreamOscillator
{
public:
	SinOsc() = default;

    bool onGetData(Chunk& data) override
    {
        // The number of samples to stream every time the function is called 
        // is equal to the buffer size of the samples vector.
		const auto amp = mAmplitude * mMaxAmp;
        for (unsigned i = 0; i < mBuffer.size(); ++i)
        {
            mBuffer[i] = amp * std::sin(mPhase); // static_cast<sf::Int16>
            UpdatePhase();
        }

        // Set the pointer to the next audio samples to be played
        data.samples = &mBuffer.front();
        data.sampleCount = mBuffer.size();

        return true;
    }
};
	