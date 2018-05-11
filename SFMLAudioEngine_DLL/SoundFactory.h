#pragma once

#include <map>
#include <memory>
#include <functional>

#include "ISoundSource.h"
#include "SoundDescription.h";

class SoundFactory
{
public:
	SoundFactory() = delete;
	~SoundFactory() = default;
	SoundFactory(const SoundFactory& other) = delete;
	SoundFactory(SoundFactory&& other) noexcept = delete;
	SoundFactory& operator=(const SoundFactory& other) = delete;
	SoundFactory& operator=(SoundFactory&& other) noexcept = delete;

	static void Initialize();
	static std::unique_ptr<ISoundSource> Create(const SoundDescription& soundDescription);

private:
    static std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(const SoundDescription&)>> mCreator;
};
