#pragma once
#include <SFML/Audio.hpp>
#include "SoundDescription.h"
#include <map>
#include <functional>

class SoundFactory
{
public:
    static sf::SoundSource* Create(const SoundDescription::SoundType soundType)
    {
        const auto ctor = mCreator.find(soundType);
        if (ctor != mCreator.end())
            return ctor->second();

        return nullptr;
    }

private:
    SoundFactory()
    {
        mCreator[SoundDescription::SoundType::STREAM] = []() {return new sf::Music(); };
        mCreator[SoundDescription::SoundType::SFX]    = []() {return new sf::Sound(); };
        //mCreator[SoundDescription::SoundType::OSC] = []() {return new sf::Sound(); };
    }

    static std::map<SoundDescription::SoundType, std::function<sf::SoundSource*()>> mCreator;
};