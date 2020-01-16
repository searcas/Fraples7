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
		FPL_PROFILE_FUNCTION();
		glfwMakeContextCurrent(_mWinHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FPL_CORE_ASSERTS(status, " Failed to initialize GLAD ");
		
		
		FPL_CORE_INFO("   INFO:: ");
		FPL_CORE_INFO("   Vendor: {0} ", glGetString(GL_VENDOR));
		FPL_CORE_INFO("   Renderer: {0} ", glGetString(GL_RENDERER));
		FPL_CORE_INFO("   Version: {0} ", glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers()
	{
		FPL_PROFILE_FUNCTION();

		glfwSwapBuffers(_mWinHandle);
	}
}