#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "FraplesSeven/Events/Events.h"
#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/ImGui/imGuiLayer.h"

#include "FraplesSeven/Core/TimeSteps.h"




namespace Fraples {

	class Application
	{

	public:
		Application();
		~Application() = default;
		void Run();
		void Close();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		static Application& GetApp() { return *_sInstance; }
		Window& GetWindow() const { return *_mWindow; }
		ImGuiLayer* GetImGuiLayer()const { return _mImguiLayer; }
	private:
		bool OnWindowsClosed(WindowCloseEvent& winEvent);
		bool OnWindowResize(WindowResizeEvent& winEvent);

	private:
		std::unique_ptr<Window>_mWindow;
		ImGuiLayer* _mImguiLayer;
		bool _mRunning = true;
		bool _mMinimized = false;
		LayerStack _mLayerStack;

		float _mLastTime = 0.0f;
	private:
		static Application* _sInstance;
	};
	//TODO Define in Client;
}