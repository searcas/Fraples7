#pragma once
#include "FraplesSeven/Renderer/Shader.h"
#include "glm/glm.hpp"



namespace Fraples
{
	typedef unsigned int GLenum;
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		//for debug purpose
		void Unbind() const override;
		const std::string& GetName() const override { return _mName; }


		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		
		void SetUniformInt(const std::string& name, int value) override;
		void SetUniformFloat(const std::string& name, float value) override;
		void SetUniformFloat3(const std::string& name, const glm::vec3& color) override;
		void SetUniformFloat4(const std::string& name, const glm::vec4& color) override;
		void SetUniformMat4(const std::string& name, const glm::mat4& mat) override;
		
		void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& readfile);
		std::unordered_map<GLenum,std::string>PreProcess(const std::string& shaderSrcCode);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t _mRendererID;
		std::string _mName;
	};
}