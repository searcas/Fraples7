#pragma once
#include <string>


namespace  Fraples
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind()const;
		//for debug purpose
		void Unbind()const;
	private:
		uint32_t _mRendererID;  
	};
}