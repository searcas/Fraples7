#pragma once
#include "FplPCH.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Fraples
{
	OpenGLContext::OpenGLContext(GLFWwindow* winHandle): _mWinHandle(winHandle)
	{
		FPL_CORE_ASSERTS(winHandle, " Window handle is null.");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(_mWinHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FPL_CORE_ASSERTS(status, " Failed to initialize GLAD ");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_mWinHandle);
	}
}