#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "Window.h"
namespace Fraples{
		
	class FPL_API Application
	{
		
	public:
	Application();
	virtual ~Application();
	
	void Run();
	private:
		std::unique_ptr<Window>_mWindow;
		bool _mRunning = true;
	};
	//TODO Define in Client;
	Application* CreateApplication();
}