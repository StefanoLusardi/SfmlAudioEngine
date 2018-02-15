#pragma once

#include "ISoundSource.h"
#include <SFML/Audio/Music.hpp>

#define TWO_PI 6.28318530718

class SoundFactory;

class StreamOscillator : public sf::SoundStream
{
public:
    StreamOscillator(const int numChannels = 1, const int sampleRate = 48000)
    {
        m_samples = std::vector<sf::Int16>(8*2048, 0);

        // reset the current playing position 
        m_currentSample = 0;

        // Init internal oscillator parameters
        Init();

        // initialize the base class
        initialize(numChannels, sampleRate);
    }
    
private:

    double mPhase;
    double mPhaseIncrement;

    void Init()
    {
        mPhase = 0; // phaseOffset;
        mPhaseIncrement = (TWO_PI * 440 / 48000);
    }

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
        // number of samples to stream every time the function is called;
        // in a more robust implementation, it should be a fixed
        // amount of time rather than an arbitrary number of samples
        //const int samplesToStream = 2048;

        // Sine Wave
        for (int i = 0; i < m_samples.size(); ++i)
        {
            m_samples[i] = 0.5 * std::sin(mPhase) * 32768;
            UpdatePhase();
        }

        // set the pointer to the next audio samples to be played
        data.samples = &m_samples[m_currentSample];
        data.sampleCount = m_samples.size();

        return true;

        // have we reached the end of the sound?
        //if (m_currentSample + samplesToStream <= m_samples.size())
        //{
        //    // end not reached: stream the samples and continue
        //    data.sampleCount = samplesToStream;
        //    m_currentSample += samplesToStream;
        //    return true;
        //}
        //else
        //{
        //    // end of stream reached: stream the remaining samples and stop playback
        //    data.sampleCount = m_samples.size() - m_currentSample;
        //    m_currentSample = m_samples.size();
        //    return false;
        //}
    }

    //std::vector<sf::Int16> m_samples;
    std::vector<sf::Int16> m_samples;
    std::size_t m_currentSample;
};

class Oscillator : public ISoundSource
{
    friend class SoundFactory;

public:
    ~Oscillator() override
    { }

    void Play() override
    {
        mOscillator->play();
    }

    void Stop() override
    {
        mOscillator->stop();
    }

    void Pause() override
    {
        mOscillator->pause();
    }
    
    void SetLoop(const bool isLoop) override
    {
        // Oscillators are always looping by definition
        return;
    }

private:
    Oscillator(const SoundDescription soundDescription) : mOscillator{std::make_unique<StreamOscillator>()}
    {
        Oscillator::SetLoop(soundDescription.mIsLoop);
    }

    std::unique_ptr<StreamOscillator> mOscillator;
};

