#pragma once
#include "SoundDescription.h"
#include <vector>

using Type	   = SoundDescription::SoundType;
using Priority = SoundDescription::Stealing;

namespace Mock
{
    // Returns a stub of Sound Descriptions to be registered by the audio engine.
	inline const std::vector<SoundDescription> GetSoundsDescriptions()
    {
        return
        {
        //  { "SoundName", SoundType,    Priority,         MixerGroup, Volume, Pitch minDist, maxDist, Loop,  3D    },
        //  { "crash",     Type::SFX,    Priority::Oldest, "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
        //  { "hihat",     Type::SFX,    Priority::Oldest, "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
        //  { "snare",     Type::SFX,    Priority::Oldest, "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
        //  { "kick",      Type::SFX,    Priority::Oldest, "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
            { "Get_Loopy", Type::STREAM, Priority::Oldest, "Music",    100.0,  1.0,  1.0,     100.0,   true,  false },
            { "SineOsc",   Type::OSC,    Priority::Oldest, "Osc",      100.0,  1.0,  1.0,     100.0,   true,  false },
			{ "sfx_1",	   Type::SFX,	 Priority::Oldest, "Sfx",      100.0,  1.0,  1.0,     100.0,   true,  false },
			{ "sfx_2",	   Type::SFX,    Priority::Oldest, "Sfx",      100.0,  1.0,  1.0,     100.0,   true,  false },
							 			  		 		 	   		    			    
			{ "voice_f",   Type::SFX,	 Priority::Oldest, "Voices",   100.0,  1.0,  1.0,     100.0,   true,  true },
			{ "voice_m",   Type::SFX,	 Priority::Oldest, "Voices",   100.0,  1.0,  1.0,     5.0,     true,  true },
							 			   			 		 	   		    
			{ "ui_1",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_2",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_3",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_4",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_5",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_6",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_7",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_8",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_9",      Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_10",     Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			{ "ui_11",     Type::SFX,	 Priority::Oldest, "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
        };
    }
}
