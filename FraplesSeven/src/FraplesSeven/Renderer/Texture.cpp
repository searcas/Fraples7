#include "FplPCH.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Fraples{
	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return Shared<OpenGLTexture2D>(width, height);
		}
		FPL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	std::shared_ptr<Texture2D> Fraples::Texture2D::Create(const std::string & filepath)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return Shared<OpenGLTexture2D>(filepath);
		}
		FPL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}