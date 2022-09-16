#pragma once
#include "Core.h"

#ifdef FPL_PLATFORM_WINDOWS

extern Fraples::Application* CreateApplication();


void main(int argc, char** argv)
{

	Fraples::Log::initialize();
	FPL_PROFILE_BEGIN_SESSION("Startup", "FraplesProfile-Startup.json");
	auto app = CreateApplication();
	FPL_PROFILE_END_SESSION();
	FPL_PROFILE_BEGIN_SESSION("RunTime", "FraplesProfile-Runtime.json");
	app->Run();
	FPL_PROFILE_END_SESSION();
	FPL_PROFILE_BEGIN_SESSION("End", "FraplesProfile-Shutdown.json");
	delete	app;
	FPL_PROFILE_END_SESSION();
	 
}

#endif // FPL_PLATFORM_WINDOWS
