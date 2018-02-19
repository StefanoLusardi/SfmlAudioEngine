#pragma once

#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

#define TWO_PI 6.28318530718

class SoundFactory;

class Interpolator
{
public:
    Interpolator()
    {
        updateStep();
        current = initial + step;
    }

    double initial;
    double current;
    double target;
    double deltaTime;
    double step;

    void updateStep() { step = (target - initial) / deltaTime; }
    double getValue() { current += step; return current; }
};

class StreamOscillator : public sf::SoundStream
{
public:
    StreamOscillator()
        : mMaxAmp{ std::numeric_limits<sf::Int16>::max() }
        , mSampleRate{ 48000 }
        , mBufferSize{ 2048 }
        , mFrequency{ 440 }
        , mAmplitude{ 1 }
        , mPhase{ 0 }
        , mPhaseIncrement{ TWO_PI * mFrequency / mSampleRate }
        , mBuffer{ std::vector<sf::Int16>(mBufferSize, 0) }
    {    
        const int numChannels = 1;
        initialize(numChannels, mSampleRate);
    }


private:
    const int mMaxAmp;
    const int mSampleRate;
    const int mBufferSize;

    double mFrequency;
    double mAmplitude;

    double mPhase;
    double mPhaseIncrement;
    std::vector<sf::Int16> mBuffer;

    //Interpolator mAmplitude;
    //Interpolator mFrequency;


    // Increment and keep phase wraped in the [0..2pi] range.
    // Must be called after each new generated sample.
    void UpdatePhase()
    {
        mPhase += mPhaseIncrement;
        if (mPhase > TWO_PI)
            mPhase -= TWO_PI;
    }

    void onSeek(sf::Time timeOffset) override
    {
        return;
    }

    bool onGetData(Chunk& data) override
    {
        // The number of samples to stream every time the function is called 
        // is equal to the buffer size of the samples vector.

        for (int i = 0; i < mBuffer.size(); ++i)
        {
            mBuffer[i] = mAmplitude * std::sin(mPhase) * mMaxAmp; // pre-multiply mAmplitude*mMaxAmp
            UpdatePhase();
        }

        /*for (int i = 0; i < mBuffer.size(); ++i)
        {
            mBuffer[i] = mAmplitude.getValue() * std::sin(mPhase) * 32767;
            mPhaseIncrement = (TWO_PI * mFrequency.getValue() / mSampleRate);
            UpdatePhase();
        }*/

        // Set the pointer to the next audio samples to be played
        data.samples = &mBuffer.front();
        data.sampleCount = mBuffer.size();

        return true;
    }
};

class Oscillator : public ISoundSource
{
    friend class SoundFactory;

public:
    ~Oscillator() override
    { }

    void Play() override  { mOscillator->play(); }
    void Stop() override  { mOscillator->stop(); }
    void Pause() override { mOscillator->pause(); }

    void SetLoop(const bool /*isLoop*/) override { /* Oscillators are always looping by definition */ }
    void SetPitch(const double pitch) override   { mOscillator->setPitch(pitch); }
    void SetVolume(const double volume) override { mOscillator->setVolume(volume); }

    double GetPitch() override { return mOscillator->getPitch(); }
    double GetVolume() override { return mOscillator->getVolume(); }

private:
    Oscillator(const SoundDescription soundDescription) 
    : mOscillator { std::make_unique<StreamOscillator>() }
    {
        Oscillator::SetLoop(soundDescription.mIsLoop);
        Oscillator::SetVolume(soundDescription.mDefaultVolume);
    }

    std::unique_ptr<StreamOscillator> mOscillator;
};

