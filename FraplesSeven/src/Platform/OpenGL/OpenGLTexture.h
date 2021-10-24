#pragma once
#include "FraplesSeven/Renderer/Texture.h"
#include "glad/glad.h"


namespace Fraples
{
	
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();
		inline uint32_t GetWidth() const override { return _mWidth; }
		inline uint32_t GetHeight() const override { return _mHeight; }
		
		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0)const override;
		bool operator ==(const Texture& rhs) const override
		{
			return _mRendererID == ((OpenGLTexture2D&)rhs)._mRendererID;
		}
	private:
		uint32_t _mWidth;
		uint32_t _mHeight;
		uint32_t _mRendererID;
		std::string _mPath;
		GLenum _mInternalFormat, _mDataFormat;
	};

}

