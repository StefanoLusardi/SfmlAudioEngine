#pragma once

#include <map>
#include <memory>
#include <functional>

#include "SoundEffect.h"
#include "SoundStream.h"
#include "Oscillator.h"
#include "SoundDescription.h"

class SoundFactory
{
public:
    static std::unique_ptr<ISoundSource> Create(const SoundDescription::SoundType soundType)
    {
        const auto ctor = mCreator.find(soundType);
        if (ctor != mCreator.end())
            return ctor->second();

        return nullptr;
    }

private:
    SoundFactory()
    {
        mCreator[SoundDescription::SoundType::STREAM] = []() {return std::make_unique<SoundStream>(); };
        mCreator[SoundDescription::SoundType::SFX]    = []() {return std::make_unique<SoundEffect>(); };
        mCreator[SoundDescription::SoundType::OSC]    = []() {return std::make_unique<Oscillator>(); };
    }

    static std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>()>> mCreator;
};
