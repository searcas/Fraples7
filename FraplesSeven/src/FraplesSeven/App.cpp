#include "FplPCH.h"
#include "App.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Input.h"
namespace Fraples{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::_sInstance = nullptr;

	Application::Application()
	{

		FPL_CORE_ASSERTS(!_sInstance, "Application already Exists");
		_sInstance = this;
		
		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		_mImguiLayer = new ImGuiLayer();
		PushOverLay(_mImguiLayer);
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClosed));

		for (auto it = _mLayerStack.end(); it != _mLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e._mHandled)
				break;
		}
	}
	bool Application::OnWindowsClosed(WindowCloseEvent& winEvent)
	{
		_mRunning = false;
		return true;
	}
	void Application::Run()
	{
		while (_mRunning)
		{
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (Layer* layer : _mLayerStack)
				layer->OnUpdate();
			//auto[x, y] = Input::GetMousePosition();
			//FPL_CLIENT_TRACE("{0},{1}", x, y);
			_mImguiLayer->Begin();
			for (Layer* layer : _mLayerStack)
				layer->OnImGuiRender();
			_mImguiLayer->End();

			_mWindow->OnUpdate();
		}

	}
	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer)
	{
		_mLayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverLay(Layer* overlay)
	{
		_mLayerStack.PushOverLay(overlay);
		overlay->OnAttach();
	}
}