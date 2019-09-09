#include "FplPCH.h"
#include <fstream>
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

namespace Fraples
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;

		if (type == "fragment" || type =="pixel")
			return GL_FRAGMENT_SHADER;
		FPL_CORE_ASSERTS(false, "Unknown Shader Type!");
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSrc = ReadFile(filepath);
		auto shaderSources = PreProcess(shaderSrc);
		Compile(shaderSources);

		// Extract name from filepath\\
		// assests/Shaders/Texture.glsl
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		_mName = filepath.substr(lastSlash,count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :_mName(name)
	{

		std::unordered_map<GLenum, std::string>sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			FPL_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& shaderSrcCode)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSrcCode.find(typeToken, 0);
		while (pos !=std::string::npos)
		{
			size_t eol = shaderSrcCode.find_first_of("\r\n", pos);
			FPL_CORE_ASSERTS(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = shaderSrcCode.substr(begin, eol - begin);
			FPL_CORE_ASSERTS(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = shaderSrcCode.find_first_not_of("\r\n", eol);
			pos = shaderSrcCode.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = shaderSrcCode.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSrcCode.size() - 1 : nextLinePos));

		}
		return shaderSources;
	}
	OpenGLShader::~OpenGLShader()
	{

	}
	void OpenGLShader::Bind()const
	{
		glUseProgram(_mRendererID);
	}
	void OpenGLShader::Unbind()const
	{
		glUseProgram(0);
	}
	void OpenGLShader::UploadUniformInt(const std::string & name, int value)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadUniformFloat(const std::string & name, float value)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string & name, const glm::vec2 & values)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string & name, const glm::vec3 & values)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}
	void OpenGLShader::UploadUniformMat3(const std::string & name, const glm::mat3 & matrix)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 & matrix)
	{
		GLint location = glGetUniformLocation(_mRendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		FPL_CORE_ASSERTS(shaderSources.size() <= 2, "Shader must be less than 3 atm.");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& keyValue : shaderSources)
		{
			GLenum shaderType = keyValue.first;
			const std::string& shaderSrc = keyValue.second;
			GLuint shader = glCreateShader(shaderType);

			const GLchar *source = shaderSrc.c_str();
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				FPL_CORE_ERROR("{0}", infoLog.data());
				FPL_CORE_ASSERTS(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;

		}
		
			glLinkProgram(program);

			// Note the different functions here: glGetProgram* instead of glGetShader*.
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

				// We don't need the program anymore.
				glDeleteProgram(program);
				for(auto id : glShaderIDs)
					glDeleteShader(id);

				FPL_CORE_ERROR("{0}", infoLog.data());
				FPL_CORE_ASSERTS(false, "Linking compilation failure!");
				return;
			}

			for (auto id : glShaderIDs)
			glDetachShader(program, id);

			_mRendererID = program;

	}

}