#pragma once

#ifdef FPL_PLATFORM_WINDOWS

extern Fraples::Application* Fraples::CreateApplication();





void main(int argc, char** argv)
{
	

	int val = (float)7.007;
	Fraples::Log::initialize();
	FPL_CORE_WARN("[Initalized log!] VAL ={0} ", val);
	FPL_CLIENT_CRITICAL("[CRITICAL] VAL = {0}", val);

	auto app = Fraples::CreateApplication();
	app->Run();
	delete	app;
	 
}

#endif // FPL_PLATFORM_WINDOWS
