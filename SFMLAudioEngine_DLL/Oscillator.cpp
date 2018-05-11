#include "stdafx.h"

#include "Oscillator.h"
#include "OscFactory.h"

std::shared_ptr<ISoundSource> Oscillator::Clone() const
{
	return std::shared_ptr<Oscillator>(new Oscillator(this->mSoundDescription));
}

void Oscillator::Play()
{
	mOscillator->play();
}

void Oscillator::Stop()
{
	mOscillator->stop();
}

void Oscillator::Pause()
{
	mOscillator->pause();
}

void Oscillator::SetLoop(const bool)
{
	/* Oscillators are always looping by definition */
}

void Oscillator::SetPitch(const double pitch)
{
	mOscillator->setPitch(pitch);
}

void Oscillator::SetVolume(const double volume)
{
	mOscillator->setVolume(volume);
}

void Oscillator::SetPosition(const AudioUtils::Vector3D& position)
{
	mOscillator->setPosition(position.x, position.y, position.z);
}

double Oscillator::GetPitch()
{
	return mOscillator->getPitch();
}

double Oscillator::GetVolume()
{
	return mOscillator->getVolume();
}

AudioUtils::Vector3D Oscillator::GetPosition()
{
	return AudioUtils::Vector3D(mOscillator->getPosition());
}

bool Oscillator::IsSourcePlaying()
{
	return mOscillator->getStatus();
}

bool Oscillator::IsMono()
{
	return true;
}

Oscillator::Oscillator(const SoundDescription& soundDescription)
	: ISoundSource{soundDescription}
	, mOscillator {CreateStreamOscillator(soundDescription.mOscType)}
{
	Oscillator::SetLoop(soundDescription.mIsLoop);
	Oscillator::SetPitch(soundDescription.mDefaultPitch);
	Oscillator::SetVolume(soundDescription.mDefaultVolume);

	mOscillator->setRelativeToListener(false);

	if (soundDescription.mIs3d && Oscillator::IsMono())
	{
		mOscillator->setAttenuation(AudioUtils::DistanceToAttenuation(soundDescription.mMaxDistance, soundDescription.mMinDistance));
		mOscillator->setMinDistance(soundDescription.mMinDistance);
	}
}

std::unique_ptr<StreamOscillator> Oscillator::CreateStreamOscillator(
	const std::optional<SoundDescription::OscType>& oscType)
{
	return OscFactory::CreateOsc(oscType);
}
