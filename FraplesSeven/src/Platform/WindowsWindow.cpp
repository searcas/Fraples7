#include"FplPCH.h"

#include"WindowsWindow.h"



namespace Fraples
{
	static bool isInitialized = false;
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
			FPL_CORE_ASSERT(success, "Could not initialize GLFW!");
			isInitialized = true;
		}
		_mWindow = glfwCreateWindow((int)prop._mWidth, (int)_mData._mHeight, _mData._mTitle.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_mWindow);
		glfwSetWindowUserPointer(_mWindow, &_mData);
		SetVSync(true);
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