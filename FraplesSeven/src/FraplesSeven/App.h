#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Events.h"
#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/ImGui/imGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
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
		static Application* _sInstance;
		unsigned int _mVertexArray;

		std::unique_ptr<Shader> _mShader;
		std::unique_ptr<VertexBuffer> _mVertexBuffer;
		std::unique_ptr<IndexBuffer> _mIndexBuffer;

	};
	//TODO Define in Client;
	Application* CreateApplication();
}