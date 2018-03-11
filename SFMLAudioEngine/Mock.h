#pragma once
#include "SoundDescription.h"
#include <vector>

using Type = SoundDescription::SoundType;

namespace Mock
{
    // Returns a stub of Sound Descriptions to be registered by the audio engine.
	inline const std::vector<SoundDescription> GetSoundsDescriptions()
    {
        return
        {
        //  { "SoundName",   SoundType,      volume,  pitch   minDistance,   maxDistance,   Loop,    3D    },
        //  { "crash",       Type::SFX,      100.0,   1.0,    1.0,           100.0,         false,   false },
        //  { "hihat",       Type::SFX,      100.0,   1.0,    1.0,           100.0,         false,   false },
        //  { "snare",       Type::SFX,      100.0,   1.0,    1.0,           100.0,         false,   false },
        //  { "kick",        Type::SFX,      100.0,   1.0,    1.0,           100.0,         false,   false },
            { "Get_Loopy",   Type::STREAM,   100.0,   1.0,    1.0,           100.0,         true,    false },
            { "SineOsc",     Type::OSC,      100.0,   1.0,    1.0,           100.0,         true,    false },
			{ "sfx_1",		 Type::SFX,		 100.0,   1.0,    1.0,           100.0,         true,    false },
			{ "sfx_2",		 Type::SFX,      100.0,   1.0,    1.0,           100.0,         false,   false },
        };
    }
}
