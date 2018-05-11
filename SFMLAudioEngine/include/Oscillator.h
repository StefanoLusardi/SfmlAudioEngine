#pragma once

#include "ISoundSource.h"
#include <SFML/Audio/SoundStream.hpp>
#include <random>

#define TWO_PI 6.28318530718

class SoundFactory;

class StreamOscillator : public sf::SoundStream
{
public:
    StreamOscillator()
        : mMaxAmp{ std::numeric_limits<sf::Int16>::max() }
        , mSampleRate{ 48000 }
        , mBufferSize{ 2048 }
        , mFrequency{ 440.0 }
        , mAmplitude{ 1.0 }
        , mPhase{ 0.0 }
        , mPhaseIncrement{ TWO_PI * mFrequency / (float)mSampleRate }
        , mBuffer{ std::vector<sf::Int16>(mBufferSize, 0) }
    {    
        const int numChannels = 1;
        initialize(numChannels, mSampleRate);
    }

protected:
    const sf::Int16 mMaxAmp;
    const int mSampleRate;
    const int mBufferSize;

    double mFrequency;
    double mAmplitude;

    double mPhase;
    double mPhaseIncrement;
    std::vector<sf::Int16> mBuffer;

    // Increment and keep phase wraped in the [0..2pi] range.
    // Must be called after each new generated sample.
    void UpdatePhase()
    {
        mPhase += mPhaseIncrement;
        if (mPhase > TWO_PI)
            mPhase -= TWO_PI;
    }

    void onSeek(sf::Time timeOffset) override {}
	bool onGetData(Chunk& data) override = 0;
};

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

class Oscillator : public ISoundSource
{
    friend class SoundFactory;

public:
	~Oscillator() override = default;

	std::shared_ptr<ISoundSource> Clone() const override { return std::shared_ptr<Oscillator>(new Oscillator(this->mSoundDescription)); }

    void Play() override  { mOscillator->play(); }
    void Stop() override  { mOscillator->stop(); }
    void Pause() override { mOscillator->pause(); }

    void SetLoop(const bool /*isLoop*/) override { /* Oscillators are always looping by definition */ }
    void SetPitch(const double pitch) override   { mOscillator->setPitch(pitch); }
    void SetVolume(const double volume) override { mOscillator->setVolume(volume); }
	void SetPosition(const AudioUtils::Vector3D& position) override { mOscillator->setPosition(position.x, position.y, position.z); }
	
    double GetPitch() override { return mOscillator->getPitch(); }
    double GetVolume() override { return mOscillator->getVolume(); }
	AudioUtils::Vector3D GetPosition() override { return AudioUtils::Vector3D(mOscillator->getPosition()); }

	bool IsSourcePlaying() override { return mOscillator->getStatus(); }
	bool IsMono() override { return true; }

private:
    std::unique_ptr<StreamOscillator> mOscillator;

    Oscillator(const SoundDescription& soundDescription) 
	: ISoundSource{ soundDescription }
    , mOscillator { CreateStreamOscillator(soundDescription.mOscType) }
    {
        Oscillator::SetLoop(soundDescription.mIsLoop);
		Oscillator::SetPitch(soundDescription.mDefaultPitch);
        Oscillator::SetVolume(soundDescription.mDefaultVolume);

    	mOscillator->setRelativeToListener(false);

		if (soundDescription.mIs3d && Oscillator::IsMono())
		{
			mOscillator->setAttenuation(DistanceToAttenuation(soundDescription.mMaxDistance, soundDescription.mMinDistance));
			mOscillator->setMinDistance(soundDescription.mMinDistance);
		}
    }

	std::unique_ptr<StreamOscillator> CreateStreamOscillator(const std::optional<SoundDescription::OscType>& oscType) const
	{
		switch(oscType.value_or(SoundDescription::OscType::SIN)) 
		{ 
		case SoundDescription::OscType::NOISE:	return std::make_unique<Noise>();
		case SoundDescription::OscType::SIN:	return std::make_unique<SinOsc>();
		default: 								return std::make_unique<SinOsc>();
		}	
	}
};
