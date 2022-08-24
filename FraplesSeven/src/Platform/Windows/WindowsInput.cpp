#include "FplPCH.h"
#include "FraplesSeven/Core/Input.h"
#include "GLFW/glfw3.h"
#include "FraplesSeven/Core/App.h"


namespace Fraples
{
	bool Input::IsKeyPressed(unsigned int keyCoede)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCoede);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(unsigned int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window,button);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	float Input::GetMouseX()
	{
		auto[x, y] = GetMousePosition();

		return x;
	}
	float Input::GetMouseY()
	{
		auto[x, y] = GetMousePosition();

		return y;
		
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x,(float)y };
	}
}