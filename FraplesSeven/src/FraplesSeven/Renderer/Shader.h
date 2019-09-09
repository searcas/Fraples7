#pragma once
#include <string>
#include <unordered_map>
namespace  Fraples
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		//for debug purpose
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;
		static std::shared_ptr<Shader> Create(const std::string& filepath);
		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};
	class ShaderLibrary
	{
	public:
		void Add(const std::shared_ptr<Shader>& shader);
		void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
		std::shared_ptr<Shader>Load(const std::string& filepath);
		std::shared_ptr<Shader>Load(const std::string& name, const std::string& filepath);

		std::shared_ptr<Shader>GetShader(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>>_mShaders;
	};
}