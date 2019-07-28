#include "FplPCH.h"
#include "App.h"
#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/Log.h"

namespace Fraples{
	
	Application::Application()
	{
		_mWindow = std::unique_ptr<Window>(Window::Create());
	}

	void Application::Run()
	{
		while (_mRunning)
		{
			_mWindow->OnUpdate();
		}

	}
	Application::~Application()
	{
	}
}