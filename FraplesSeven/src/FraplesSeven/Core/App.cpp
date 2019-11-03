#include "FplPCH.h"
#include "App.h"


#include "Input.h"

#include "FraplesSeven/Renderer/Renderer.h"

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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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
	bool Application::OnWindowResize(WindowResizeEvent& winEvent)
	{
		if (winEvent.GetWidth() == 0 || winEvent.GetHeight() == 0)
		{
			_mMinimized = true;
			return false;
		}
		_mMinimized = false;
		Renderer::OnWindowResize(winEvent.GetWidth(), winEvent.GetHeight());
		return false;
	}
	void Application::Run()
	{
		while (_mRunning)
		{
			float time = (float)glfwGetTime();
			TimeSteps timesteps = time - _mLastTime;
			_mLastTime = time;
			if (!_mMinimized)
			{
				for (Layer* layer : _mLayerStack)
					layer->OnUpdate(timesteps);

			}
			_mImguiLayer->Begin();
			for (Layer* layer : _mLayerStack)
				layer->OnImGuiRender();
			_mImguiLayer->End();
			//auto[x, y] = Input::GetMousePosition();
			//FPL_CLIENT_TRACE("{0},{1}", x, y);

			_mWindow->OnUpdate();
		}

	}
	void Application::PushLayer(Layer* layer)
	{
		_mLayerStack.PushLayer(layer);
	
	}
	void Application::PushOverLay(Layer* overlay)
	{
		_mLayerStack.PushOverLay(overlay);
	
	}
}