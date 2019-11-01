#include "FplPCH.h"
#include "VertexArray.h"
#include "Renderer.h"


#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fraples
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}

}