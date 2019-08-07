#include"FplPCH.h"
#include"WindowsWindow.h"

#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/Events/MouseEvent.h"
#include "FraplesSeven/Events/KeyEvent.h"

#include "glad/glad.h"

namespace Fraples
{
	static bool isInitialized = false;

	static void GLFWErrorCallBack(int error, const char* description)
	{
		FPL_CORE_ERROR("GLFW Error:({0}) ({1}) ", error, description);
	}
	Window* Window::Create(const WindowProperties& prop)
	{
		return new WindowsWindow(prop);
	}
	WindowsWindow::WindowsWindow(const WindowProperties& prop)
	{
		Init(prop);
	}
	WindowsWindow::~WindowsWindow() { ShutDown(); }

	void WindowsWindow::Init(const WindowProperties& prop)
	{
		_mData._mTitle = prop._mTitle;
		_mData._mWidth = prop._mWidth;
		_mData._mHeight = prop._mHeight;

		FPL_CORE_INFO("Creating Window {0} ({1}, {2})", prop._mTitle, prop._mWidth, prop._mHeight);

		if (!isInitialized)
		{
			//TODO:GLFW terminate on system shutdown

			int success = glfwInit();
			FPL_CORE_ASSERTS(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallBack);
			isInitialized = true;
		}
		_mWindow = glfwCreateWindow((int)prop._mWidth, (int)_mData._mHeight, _mData._mTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_mWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FPL_CORE_ASSERTS(status, "Fail to initialize GLAD!");
		glfwSetWindowUserPointer(_mWindow, &_mData);
		SetVSync(true);
		// Set GLFW callbacks

		glfwSetWindowSizeCallback(_mWindow, [](GLFWwindow* window, int width, int height)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data._mWidth = width;
				data._mHeight = height;
				
				WindowResizeEvent event(width, height);
				data._mEventCallbackFn(event);
		});
		glfwSetWindowCloseCallback(_mWindow,[](GLFWwindow* window)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data._mEventCallbackFn(event);
		});
		glfwSetKeyCallback(_mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data._mEventCallbackFn(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data._mEventCallbackFn(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent pressEvent(key,1);
						data._mEventCallbackFn(pressEvent);
						break;
					}
				}
		});
		glfwSetCharCallback(_mWindow, [](GLFWwindow* window, unsigned  int c)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent eve(c);
				data._mEventCallbackFn(eve);
		});
		glfwSetMouseButtonCallback(_mWindow, [](GLFWwindow* window, int button,  int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch (action)
				{
				case GLFW_PRESS:
				{
					 MouseButtonPressedEvent event(button);
					data._mEventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data._mEventCallbackFn(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(_mWindow, [](GLFWwindow* window, double xOffset, double yOffset) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrollEvent event((float)xOffset,(float)yOffset);
				data._mEventCallbackFn(event);
		});
		glfwSetCursorPosCallback(_mWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data._mEventCallbackFn(event);

		});
	}
	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(_mWindow);
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_mData._mVSync = enabled;
	}
	bool WindowsWindow::IsVSync()const
	{
		return _mData._mVSync;
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_mWindow);

	}
}