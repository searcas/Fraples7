#include "FplPCH.h"	
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
namespace Fraples
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}
	


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}
}