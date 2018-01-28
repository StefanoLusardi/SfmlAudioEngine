#include "SoundObject.h"

// Initialize SoundFactory static map of SoundSource constructors
std::map<SoundDescription::SoundType, std::function<sf::SoundSource*()>> SoundFactory::mCreator = {};

SoundObject::SoundObject(const SoundDescription description)
: mDescription(description)
, mSoundSource(nullptr)
{
    mSoundSource = SoundFactory::Create(mDescription.mSoundType);
    //mSoundBuffer->loadFromStream();
}

SoundObject::~SoundObject()
{
    delete mSoundSource;
    delete mSoundBuffer;
}

void SoundObject::Play()
{
}

void SoundObject::Stop()
{
}
