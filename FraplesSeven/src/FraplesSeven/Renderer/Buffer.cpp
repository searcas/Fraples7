#include "FplPCH.h"	
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Fraples
{
	VertexBuffer::~VertexBuffer()
	{
	}
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}
}