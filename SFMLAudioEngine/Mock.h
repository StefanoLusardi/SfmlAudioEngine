#pragma once
#include "SoundDescription.h"
#include <vector>

using Type	   = SoundDescription::SoundType;
using Stealing = SoundDescription::StealingPolicy;

namespace Mock
{
    // Returns a stub of Sound Descriptions to be registered by the audio engine.
	inline std::vector<SoundDescription> GetSoundsDescriptions()
    {
        return
        {
        //  { "SoundName", SoundType,    MixerGroup, Volume, Pitch minDist, maxDist, Loop,  3D    },
			//{ "crash",     Type::SFX,    "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
			//{ "hihat",     Type::SFX,    "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
			//{ "snare",     Type::SFX,    "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },
			//{ "kick",      Type::SFX,    "Drums",    100.0,  1.0,  1.0,     100.0,   false, false },

            //{ "Get_Loopy", Type::STREAM, "Music",    100.0,  1.0,  1.0,     100.0,   true,  false },

            { "SineOsc",   Type::OSC,    "Osc",      100.0,  1.0,  1.0,     100.0,   true,  false },

			{ "sfx_1",	   Type::SFX,	 "Sfx",      100.0,  1.0,  1.0,     100.0,   true,  false },
			{ "sfx_2",	   Type::SFX,    "Sfx",      100.0,  1.0,  1.0,     100.0,   true,  false },
							 			 	   		    			    
			{ "voice_f",   Type::SFX,	 "Voices",   100.0,  1.0,  1.0,     100.0,   true,  true },
			{ "voice_m",   Type::SFX,	 "Voices",   100.0,  1.0,  1.0,     5.0,     true,  true },
							 			 	 	   		    
			//{ "ui_1",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_2",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_3",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_4",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_5",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_6",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_7",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_8",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_9",      Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_10",     Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
			//{ "ui_11",     Type::SFX,	 "Ui",       100.0,  1.0,  1.0,     100.0,   false, true },
        };
    }

	inline std::vector<std::tuple<const std::string, const int, const Stealing>> GetGroupSettings()
	{
		return
		{
			{ "Drums",  4, Stealing::NONE   },
			{ "Music",  2, Stealing::NONE	},
			{ "Osc",    5, Stealing::OLDEST },
			{ "Sfx",    1, Stealing::OLDEST },
			{ "Voices", 1, Stealing::NONE	},
			{ "Ui",     3, Stealing::OLDEST },
		};
	}

	// Returns a stub of Mixer Groups structure defined by the user.
	//inline const ??? GetMixerGroups()

	// Returns a stub of Mixer Snapshots structure defined by the user.
	//inline const ??? GetMixerSnapshots()
}
