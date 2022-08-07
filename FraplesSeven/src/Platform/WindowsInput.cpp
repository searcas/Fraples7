#include "FplPCH.h"
#include "Platform/WindowsInput.h"

#include"GLFW/glfw3.h"
#include "FraplesSeven/Core/App.h"


namespace Fraples
{
	Input* Input::_sInstance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCoede)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCoede);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window,button);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePosImpl();

		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePosImpl();

		return y;
		
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x,(float)y };
	}
}