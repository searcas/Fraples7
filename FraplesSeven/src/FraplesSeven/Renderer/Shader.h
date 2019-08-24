#pragma once
#include <string>
#include "glm/glm.hpp"

namespace  Fraples
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		//for debug purpose
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t _mRendererID;  
	};
}