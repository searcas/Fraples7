#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Events.h"
#include "FraplesSeven/Events/AppEvent.h"

namespace Fraples{
		
	class FPL_API Application
	{
		
	public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverLay(Layer* layer);

	inline static Application& GetApp() { return *_sInstance; }
	inline Window& GetWindow()   { return *_mWindow; }
	private:
		bool OnWindowsClosed(WindowCloseEvent& winEvent);
		std::unique_ptr<Window>_mWindow;
		bool _mRunning = true;

		LayerStack _mLayerStack;
	private:
		static Application* _sInstance;

	};
	//TODO Define in Client;
	Application* CreateApplication();
}