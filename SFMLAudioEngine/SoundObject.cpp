#include "SoundObject.h"

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<sf::SoundSource*()>> SoundFactory::mCreator = {};

SoundObject::SoundObject(const SoundDescription description)
: mDescription(description)
, mSoundSource(nullptr)
{
    mSoundSource = SoundFactory::Create(mDescription.mSoundType);
}

SoundObject::~SoundObject()
{
}
