#pragma once

#ifdef FPL_PLATFORM_WINDOWS
#ifdef FPL_BUILD_DLL
	#define FPL_API __declspec(dllexport)
#else
	#define FPL_API __declspec(dllimport)
#endif // FPL_BUILD_DLL
#else
	#error Fraples only supports Windows!
#endif // FPL_PLATFORM_WINDOWS


#ifdef FPL_ENABLE_ASSERTS
	#define FPL_CLIENT_ASSERTS(x, ...) { if(!(x)) {Fpl_ERROR("Assertion Failed: {0} ",__VA_ARGS__); __debugbreak(); } }
	#define FPL_CORE_ASSERT (x, ...) {if (!(x)){ Fpl_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak(); } }
#else
	#define FPL_CLIENT_ASSERT(x, ...)
	#define FPL_CORE_ASSERT(x, ...)
#endif


#define BIT(X)	(1 << X)
