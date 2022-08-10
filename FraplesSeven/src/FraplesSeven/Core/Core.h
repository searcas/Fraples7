#pragma once

#include <memory>
#include "Log.h"
// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define FPL_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define FPL_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define FPL_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define FPL_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define FPL_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef FPL_DEBUG
#if defined(FPL_PLATFORM_WINDOWS)
#define FPL_DEBUGBREAK() __debugbreak()
#elif defined(FPL_PLATFORM_LINUX)
#include <signal.h>
#define FPL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define FPL_ENABLE_ASSERTS
#else
#define FPL_DEBUGBREAK()
#endif

#ifdef FPL_ENABLE_ASSERTS
#define FPL_ASSERT(x, ...) { if(!(x)) { assert("Assertion Failed: {0}", __VA_ARGS__); FPL_DEBUGBREAK(); } }
#define FPL_CORE_ASSERT(x, ...) { if(!(x)) { FPL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); FPL_DEBUGBREAK(); } }
#else
#define FPL_ASSERT(x, ...)
#define FPL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FPL_BIND_EVENT_FN(fn) [this](auto&&...args) -> decltype(auto){ return this->fn(std::forward<decltype(args)>(args)...); }

namespace Fraples {

	template<typename T>
	using unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr unique<T> Unique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr shared<T> Shared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}