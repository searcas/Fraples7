#include "FplPCH.h"
#include "Shader.h"
#include "Renderer.h"


#include "Platform/OpenGL/OpenGLShader.h"

namespace Fraples
{
	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		FPL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	std::shared_ptr<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::NONE:
			FPL_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		FPL_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	

	void  ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
	
		FPL_CORE_ASSERT(Exists(name), "Shader already exist!!");
		_mShaders[name] = shader;
	}
	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		FPL_CORE_ASSERT(!Exists(name), "Shader not folund!");
		return _mShaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return _mShaders.find(name) == _mShaders.end();
	}

}