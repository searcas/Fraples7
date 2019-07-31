#include "FplPCH.h"
#include "App.h"


#include "GLFW/glfw3.h"

#include "glad/glad.h"
namespace Fraples{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::_sInstance = nullptr;

	Application::Application()
	{

		FPL_CORE_ASSERTS(!_sInstance, "Application already Exists");
		_sInstance = this;
		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClosed));
		FPL_CORE_TRACE("{0}", e);

		for (auto it = _mLayerStack.end(); it < _mLayerStack.begin(); it++)
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
			for (Layer* layer : _mLayerStack)
				layer->OnUpdate();

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