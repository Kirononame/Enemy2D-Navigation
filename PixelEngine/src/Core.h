#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API _declspec(dllexport)
	#else
		#define ENGINE_API _declspec(dllimport)
	#endif
#else
	#error PLATFORM NOT SUPPORTED
#endif 

