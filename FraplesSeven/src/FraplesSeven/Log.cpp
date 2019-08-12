#include "FplPCH.h"
#include "Log.h"


namespace Fraples{
	
	std::shared_ptr<spdlog::logger> Log::_sClientLogger;
	std::shared_ptr<spdlog::logger> Log::_sCoreLogger;

	void Log::initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_sCoreLogger = spdlog::stdout_color_mt("FraplesEngine7: ");
		_sCoreLogger->set_level(spdlog::level::trace);

		_sClientLogger = spdlog::stdout_color_mt("Application: ");
		_sClientLogger->set_level(spdlog::level::trace);

	}
}