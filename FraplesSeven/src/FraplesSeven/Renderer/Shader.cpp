#include "FplPCH.h"
#include "Shader.h"
#include "Renderer.h"


#include "Platform/OpenGL/OpenGLShader.h"

namespace Fraples
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERTS(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		FPL_CORE_ASSERTS(false, "Unknown RendererAPI");
		return nullptr;
	}
	

}