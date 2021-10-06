#pragma once
#include "Core.h"

#ifdef FPL_PLATFORM_WINDOWS

extern Fraples::Application* CreateApplication();





void main(int argc, char** argv)
{
	

	Fraples::Log::initialize();

	FPL_PROFILE_SESSION_BEGIN("Startup", "FraplesProfile-Startup.json");
	auto app = CreateApplication();
	FPL_PROFILE_SESSION_END();
	FPL_PROFILE_SESSION_BEGIN("RunTime", "FraplesProfile-Runtime.json");
	app->Run();
	
	FPL_PROFILE_SESSION_END();

	FPL_PROFILE_SESSION_BEGIN("End", "FraplesProfile-Shutdown.json");
	delete	app;
	FPL_PROFILE_SESSION_END();
	 
}

#endif // FPL_PLATFORM_WINDOWS
