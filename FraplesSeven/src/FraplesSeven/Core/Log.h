#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Fraples
{
	class Log
	{
	public:
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return _sCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return _sClientLogger; }
		static void initialize();

	private:
		static std::shared_ptr<spdlog::logger> _sCoreLogger;
		static std::shared_ptr<spdlog::logger> _sClientLogger;
	};
}
//Core log macro
#define FPL_CORE_CRITICAL(...) ::Fraples::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define FPL_CORE_ERROR(...) ::Fraples::Log::GetCoreLogger()->error(__VA_ARGS__);
#define FPL_CORE_WARN(...) ::Fraples::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define FPL_CORE_INFO(...) ::Fraples::Log::GetCoreLogger()->info(__VA_ARGS__);
#define FPL_CORE_TRACE(...) ::Fraples::Log::GetCoreLogger()->trace(__VA_ARGS__);
//Client log macro
#define FPL_CLIENT_CRITICAL(...) ::Fraples::Log::GetClientLogger()->critical(__VA_ARGS__);
#define FPL_CLIENT_ERROR(...) ::Fraples::Log::GetClientLogger()->error(__VA_ARGS__);
#define FPL_CLIENT_WARN(...) ::Fraples::Log::GetClientLogger()->warn(__VA_ARGS__);
#define FPL_CLIENT_INFO(...) ::Fraples::Log::GetClientLogger()->info(__VA_ARGS__);
#define FPL_CLIENT_TRACE(...) ::Fraples::Log::GetClientLogger()->trace(__VA_ARGS__);