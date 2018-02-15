#pragma once
#include "SoundDescription.h"
#include <vector>

using Type = SoundDescription::SoundType;

namespace Mock
{
    // Returns a stub of Sound Descriptions to be registered by the audio engine.
    const std::vector<SoundDescription> GetSoundsDescriptions()
    {
        return
        {
        //  { "SoundName",   SoundType,      volume,   minDistance,   maxDistance,   Loop,    3D    },
            { "crash",       Type::SFX,      1.0,      1.0,           100.0,         false,   false },
            { "hihat",       Type::SFX,      1.0,      1.0,           100.0,         false,   false },
            { "snare",       Type::SFX,      1.0,      1.0,           100.0,         false,   false },
            { "kick",        Type::SFX,      1.0,      1.0,           100.0,         false,   false },
            { "Get_Loopy",   Type::STREAM,   1.0,      1.0,           100.0,         true,    false },
            { "SineOsc",     Type::OSC,      1.0,      1.0,           100.0,         true,   false },
        };
    }
}
