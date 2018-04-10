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

	SoundFactory() = delete;
	~SoundFactory() = default;

    static std::unique_ptr<ISoundSource> Create(const SoundDescription& soundDescription)
    {
        const auto ctor = mCreator.find(soundDescription.mSoundType);
        if (ctor != mCreator.end())
            return ctor->second(soundDescription);

        return nullptr;
    }

    static void Initialize()
    {
        // std::make_unique<>() function won't work here beacause it's not a member function of this class and so it can't be frien of the 3 created classes
        // See https://stackoverflow.com/questions/29896268/friend-function-is-unable-to-construct-a-unique-pointer-of-the-class
        mCreator[SoundDescription::SoundType::STREAM] = [](const SoundDescription& soundDescription) {return std::unique_ptr<SoundStream>(new SoundStream(soundDescription)); };
        mCreator[SoundDescription::SoundType::SFX]    = [](const SoundDescription& soundDescription) {return std::unique_ptr<SoundEffect>(new SoundEffect(soundDescription)); };
        mCreator[SoundDescription::SoundType::OSC]    = [](const SoundDescription& soundDescription) {return std::unique_ptr<Oscillator> (new Oscillator (soundDescription)); };
    }

private:

    static std::map<SoundDescription::SoundType, std::function<std::unique_ptr<ISoundSource>(const SoundDescription&)>> mCreator;
};
