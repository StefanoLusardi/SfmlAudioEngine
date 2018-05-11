#pragma once

#include <random>
#include "StreamOscillator.h"

class Noise : public StreamOscillator
{
public:
	Noise() : gen{rd()}, dis{-1.0, 1.0} { }

    bool onGetData(Chunk& data) override
    {
        // The number of samples to stream every time the function is called 
        // is equal to the buffer size of the samples vector.
		const auto amp = mAmplitude * mMaxAmp;
        for (unsigned i = 0; i < mBuffer.size(); ++i)
        {
            mBuffer[i] = amp * dis(gen);
        }

        // Set the pointer to the next audio samples to be played
        data.samples = &mBuffer.front();
        data.sampleCount = mBuffer.size();

        return true;
    }

private:
		std::random_device rd;
		std::mt19937 gen; 
		std::uniform_real_distribution<> dis;
};
