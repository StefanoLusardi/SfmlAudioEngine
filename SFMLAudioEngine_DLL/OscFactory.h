#pragma once

#include <memory>

#include "SoundDescription.h"
#include "StreamOscillator.h"

class OscFactory
{
public:
	OscFactory() = delete;
	~OscFactory() = default;
	OscFactory(const OscFactory& other) = delete;
	OscFactory(OscFactory&& other) noexcept = delete;
	OscFactory& operator=(const OscFactory& other) = delete;
	OscFactory& operator=(OscFactory&& other) noexcept = delete;

	static std::unique_ptr<StreamOscillator> CreateOsc(const std::optional<SoundDescription::OscType>& oscType);
};
