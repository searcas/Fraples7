#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "FraplesSeven/Events/AppEvent.h"
#include "Window.h"

namespace Fraples{
		
	class FPL_API Application
	{
		
	public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);
	private:
		bool OnWindowsClosed(WindowCloseEvent& winEvent);
		std::unique_ptr<Window>_mWindow;
		bool _mRunning = true;
	};
	//TODO Define in Client;
	Application* CreateApplication();
}