#include "stdafx.h"

#include "OscFactory.h"
#include "Noise.h"
#include "SinOsc.h"

std::unique_ptr<StreamOscillator> OscFactory::CreateOsc(const std::optional<SoundDescription::OscType>& oscType)
{
	switch (oscType.value_or(SoundDescription::OscType::SIN))
	{
		case SoundDescription::OscType::NOISE : return std::make_unique<Noise>();
		case SoundDescription::OscType::SIN :	return std::make_unique<SinOsc>();
		default :								return std::make_unique<SinOsc>();
	}
}
