#pragma once

#include "ISoundSource.h"
#include "StreamOscillator.h"

class SoundFactory;

class Oscillator : public ISoundSource
{
    friend class SoundFactory;

public:
	~Oscillator() override = default;

	std::shared_ptr<ISoundSource> Clone() const override;

	void Play() override;
	void Stop() override;
	void Pause() override;

	void SetLoop(const bool /*isLoop*/) override;
	void SetPitch(const double pitch) override;
	void SetVolume(const double volume) override;
	void SetPosition(const AudioUtils::Vector3D& position) override;

	double GetPitch() override;
	double GetVolume() override;
	AudioUtils::Vector3D GetPosition() override;

	bool IsSourcePlaying() override;
	bool IsMono() override;

private:
    std::unique_ptr<StreamOscillator> mOscillator;
	Oscillator(const SoundDescription& soundDescription);
	static std::unique_ptr<StreamOscillator> CreateStreamOscillator(const std::optional<SoundDescription::OscType>& oscType);
};
