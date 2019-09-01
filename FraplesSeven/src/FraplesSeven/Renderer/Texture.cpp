#include "FplPCH.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Fraples{

	std::shared_ptr<Texture2D> Fraples::Texture2D::Create(const std::string & filepath)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filepath);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
		return std::shared_ptr<Texture2D>();
	}
}