#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Events.h"
#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/ImGui/imGuiLayer.h"

#include "FraplesSeven/Core/TimeSteps.h"




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

		ImGuiLayer* _mImguiLayer;
		bool _mRunning = true;
		LayerStack _mLayerStack;
	private:
		float _mLastTime = 0.0f;
	private:
		static Application* _sInstance;
	private:


	};
	//TODO Define in Client;
	Application* CreateApplication();
}