#pragma once
#include "FraplesSeven/Renderer/Context/GraphicsContext.h"

struct GLFWwindow;

namespace Fraples
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* winHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* _mWinHandle; 

	};
}