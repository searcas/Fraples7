#include "FplPCH.h"
#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Renderer.h"
namespace Fraples
{
	FrameBuffer::FrameBuffer()
	{

	}
	shared<FrameBuffer>FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return Shared<OpenGLFrameBuffer>(spec);
		}
	}

}