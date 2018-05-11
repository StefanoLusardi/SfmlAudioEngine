#pragma once

#ifdef SFMLAUDIOENGINEDLL_EXPORTS
	#define SL_API __declspec(dllexport)
#else
	#define SL_API __declspec(dllimport)
#endif