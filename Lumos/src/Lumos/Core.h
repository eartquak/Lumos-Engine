#pragma once

#ifdef LUMOS_PLATFORM_WINDOWS
	#ifdef LUMOS_BUILD_DLL
		#define LUMOS_API __declspec(dllexport)
	#else
		#define LUMOS_API __declspec(dllimport)
	#endif
#else
#error only windows suppport for now
#endif

