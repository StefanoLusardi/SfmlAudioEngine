#pragma once

#include <map>
#include <memory>
#include <functional>

#include "SoundEffect.h"
#include "SoundStream.h"
#include "Oscillator.h"

class SoundFactory
{
public:
    static std::unique_ptr<ISoundSource> Create(const SoundDescription::SoundType soundType, const std::string soundPath)
    {
        const auto ctor = mCreator.find(soundType);
        if (ctor != mCreator.end())
            return ctor->second(soundPath);

        return nullptr;
    }

    static void Initialize()
    {
        // std::make_unique<>() function won't work here beacause it's not a member function of this class and so it can't be frien of the 3 created classes
        // See https://stackoverflow.com/questions/29896268/friend-function-is-unable-to-construct-a-unique-pointer-of-the-class
        mCreator[SoundDescription::SoundType::SFX]    = [](const std::string soundPath) {return std::unique_ptr<SoundEffect>(new SoundEffect(soundPath)); };
        mCreator[SoundDescription::SoundType::STREAM] = [](const std::string soundPath) {return std::unique_ptr<SoundStream>(new SoundStream(soundPath)); };
        mCreator[SoundDescription::SoundType::OSC]    = [](const std::string soundPath) {return std::unique_ptr<Oscillator>(new Oscillator()); };
    }

    ~SoundFactory()
    { }

private:
    SoundFactory()
    { }

    static std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(std::string)>> mCreator;
};
