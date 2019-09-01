#include "FplPCH.h"
#include "App.h"


#include "Input.h"

#include "Renderer/Renderer.h"

#include "GLFW/glfw3.h"
namespace Fraples{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::_sInstance = nullptr;

	

	Application::Application() 
	{

		FPL_CORE_ASSERTS(!_sInstance, "Application already Exists");
		_sInstance = this;

		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

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
			float time = (float)glfwGetTime();
			TimeSteps timesteps = time - _mLastTime;
			_mLastTime = time;
			for (Layer* layer : _mLayerStack)
				layer->OnUpdate(timesteps);
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