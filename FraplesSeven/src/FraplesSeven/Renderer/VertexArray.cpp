#include "FplPCH.h"
#include "VertexArray.h"
#include "Renderer.h"


#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fraples
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}

}