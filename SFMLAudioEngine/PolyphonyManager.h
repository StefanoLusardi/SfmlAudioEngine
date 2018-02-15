#pragma once

class PolyphonyManager
{
public:
    enum class VirtualVoiceSettings {OLDEST, VOLUME, DISTANCE};

    explicit PolyphonyManager(const int maxInstance
        , const int maxLoadedSound
        , const VirtualVoiceSettings vistualVoiceSettings = VirtualVoiceSettings::OLDEST)
    : mMaxInstances{ maxInstance }
    , mMaxLoadedSounds{ maxLoadedSound }
    , mVirtualizeSettings{ vistualVoiceSettings }
    { }

    ~PolyphonyManager()
    { }

    const int GetMaxInstances() const { return mMaxInstances; }
    const int GetMaxLoadedSounds() const { return mMaxLoadedSounds; }
    const VirtualVoiceSettings GetVirtualVoiceSettings() const { return mVirtualizeSettings; }

private:
    const int mMaxInstances;
    const int mMaxLoadedSounds;
    VirtualVoiceSettings mVirtualizeSettings;
};
