#pragma once
#ifdef FPL_PLATFORM_WINDOWS
#if FPL_DYNAMIC_LINK
#ifdef FPL_BUILD_DLL
	#define FPL_API __declspec(dllexport)
#else
	#define FPL_API __declspec(dllimport)
#endif // FPL_BUILD_DLL
#else
	#define FPL_API
#endif
#else
	#error Fraples only supports Windows!
#endif // FPL_PLATFORM_WINDOWS

#ifdef FPL_DEBUG
	#define FPL_ENABLE_ASSERTS
#endif

#ifdef FPL_ENABLE_ASSERTS
	#define FPL_CORE_ASSERTS(x, ...) {if (!(x)) { FPL_CORE_ERROR("Assertion Failed: {0} ",__VA_ARGS__);__debugbreak(); } }
	#define FPL_CLIENT_ASSERTS(x, ...) { if(!(x)) { FPL_CLIENT_ERROR("Assertion Failed: {0} ",__VA_ARGS__); __debugbreak(); } }
#else
	#define FPL_CLIENT_ASSERT(x, ...)
	#define FPL_CORE_ASSERT(x, ...)
#endif


#define BIT(X)	(1 << X)

#define FplBindeventFn(x) std::bind(&x, this, std::placeholders::_1)