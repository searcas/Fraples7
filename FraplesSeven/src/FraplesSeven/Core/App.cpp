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

		FPL_PROFILE_FUNCTION();
		FPL_CORE_ASSERT(!_sInstance, "Application already Exists");
		_sInstance = this;

		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		_mImguiLayer = new ImGuiLayer();
		PushOverLay(_mImguiLayer);

	
	}
	void Application::OnEvent(Event& e)
	{
		FPL_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClosed));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = _mLayerStack.rbegin(); it != _mLayerStack.rend(); ++it)
		{
			if (e._mHandled)
				break;
			(*it)->OnEvent(e);

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
		FPL_PROFILE_FUNCTION();
		while (_mRunning)
		{
			FPL_PROFILE_SCOPE("RUN LOOP");
			float time = (float)glfwGetTime();
			TimeSteps timesteps = time - _mLastTime;
			_mLastTime = time;
			if (!_mMinimized)
			{
				{
					FPL_PROFILE_SCOPE("LayerStack OnUpdates");
				for (Layer* layer : _mLayerStack)
					layer->OnUpdate(timesteps);
				}
			}
			_mImguiLayer->Begin();
			{

				FPL_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : _mLayerStack)
				layer->OnImGuiRender();
			}
			_mImguiLayer->End();
			//auto[x, y] = Input::GetMousePosition();
			//FPL_CLIENT_TRACE("{0},{1}", x, y);

			_mWindow->OnUpdate();
		}

	}
	void Application::PushLayer(Layer* layer)
	{
		FPL_PROFILE_FUNCTION();
		_mLayerStack.PushLayer(layer);
		layer->OnAttach();
	
	}
	void Application::PushOverLay(Layer* overlay)
	{
		FPL_PROFILE_FUNCTION();
		_mLayerStack.PushOverLay(overlay);
		overlay->OnAttach();
	}
}