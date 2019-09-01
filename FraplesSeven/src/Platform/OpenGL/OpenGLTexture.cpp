#include "FplPCH.h"
#include "OpenGLTexture.h"

#include "glad/glad.h"
#include "stb_image.h"



namespace Fraples
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string & filepath) :_mPath(filepath)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);  
		stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		FPL_CORE_ASSERTS(data, "Fail to load images");
		_mWidth = width;
		_mHeight = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		FPL_CORE_ASSERTS(internalFormat && dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_mRendererID);
		glTextureStorage2D(_mRendererID, 1, internalFormat, _mWidth, _mHeight);

		glTextureParameteri(_mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_mRendererID, 0, 0, 0, _mWidth, _mHeight, dataFormat , GL_UNSIGNED_BYTE, data);

		stbi_image_free(data); 
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_mRendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, _mRendererID);
	}
}