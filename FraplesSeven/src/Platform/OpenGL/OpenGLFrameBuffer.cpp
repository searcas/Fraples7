#include "FplPCH.h"
#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"

namespace Fraples
{
	static constexpr int _sMaxFrameBufferSize = 8192;

	static bool IsDepthBufferFormat(FrameBufferTextureFormat format)
	{
		switch (format)
		{
		case Fraples::FrameBufferTextureFormat::DEPTH24STENCIL8:
			return true;
		}
		return false;
	}
	static GLenum TextureTarget(bool multisample)
	{
		return multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}
	static void CreateTextures(bool multisample, uint32_t* outID, uint32_t count)
	{
		glCreateTextures(TextureTarget(multisample), count, outID);
	}
	static void BindTexture(bool multisample, uint32_t id)
	{
		glBindTexture(TextureTarget(multisample), id);
	}
	static void AttachColorTexture(uint32_t id, int samples, GLenum internalformat, GLenum format, uint32_t width, uint32_t height, int index)
	{
		bool multisample = samples > 1;
		if (multisample)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisample), id, 0);

	}

	static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
	{
		bool multisample = samples > 1;
		if (multisample)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else
		{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
			
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisample), id, 0);
	}
	static GLenum EngineFBTextureFormatToGL(FrameBufferTextureFormat format)
	{ 
		switch (format)
		{
		case Fraples::FrameBufferTextureFormat::None:
			return GL_NONE;
			break;
		case Fraples::FrameBufferTextureFormat::RED_INTEGER:
			return GL_RED_INTEGER;
			break;
		case Fraples::FrameBufferTextureFormat::RGBA8:
			return GL_RGBA8;
			break;
		case Fraples::FrameBufferTextureFormat::DEPTH24STENCIL8:
			return GL_DEPTH24_STENCIL8;
			break;
		}
		FPL_CORE_ASSERT("WRONG FrameBufferFormat", false);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec& spec) :
		_mFrameBufferSpec(spec)
	{
		for (auto& format : _mFrameBufferSpec.Attachments.Attachments)
		{
			if (!IsDepthBufferFormat(format.TextureFormat))
			{
				_mColorAttachmentSpecification.emplace_back(format.TextureFormat);
			}
			else
			{
				_mDepthAttachmentSpecification = format.TextureFormat;
			}
		}
		Validate();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &_mRendererID);
		glDeleteTextures(_mColorAttachments.size(), _mColorAttachments.data());
		glDeleteTextures(1, &_mDepthAttachment);
	}
	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _mRendererID); 
		glViewport(0, 0, _mFrameBufferSpec.width, _mFrameBufferSpec.height);


	}
	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > _sMaxFrameBufferSize || height > _sMaxFrameBufferSize)
		{
			FPL_CORE_WARN("Attempted to resize to width: {0} height: {1}  ", width, height);
			return;
		}
		_mFrameBufferSpec.width = width;
		_mFrameBufferSpec.height = height;
		Validate();
	}
	int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		FPL_CORE_ASSERT("Index is out of range ",attachmentIndex < _mColorAttachments.size());

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1,GL_RED_INTEGER,GL_INT, &pixelData);
		return pixelData;
	}
	void OpenGLFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		FPL_CORE_ASSERT("Index is out of range ", attachmentIndex < _mColorAttachments.size());
		auto& spec = _mColorAttachmentSpecification[attachmentIndex];

		glClearTexImage(_mColorAttachments[attachmentIndex], 0, 
			EngineFBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);

	}
	void OpenGLFrameBuffer::Validate()
	{
		if (_mRendererID)
		{
			glDeleteFramebuffers(1, &_mRendererID);
			glDeleteTextures( _mColorAttachments.size(), _mColorAttachments.data());
			glDeleteTextures(1, &_mDepthAttachment);

			_mColorAttachments.clear();
			_mDepthAttachment = 0;
		}

		glCreateFramebuffers(1, &_mRendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, _mRendererID);
		bool multisample = _mFrameBufferSpec.samples > 1;

		if (_mColorAttachmentSpecification.size())
		{
			_mColorAttachments.resize(_mColorAttachmentSpecification.size());
			CreateTextures(multisample, _mColorAttachments.data(), _mColorAttachments.size());

			for (size_t i = 0; i < _mColorAttachments.size(); i++)
			{
				BindTexture(multisample, _mColorAttachments[i]);
				switch (_mColorAttachmentSpecification[i].TextureFormat)
				{
				case FrameBufferTextureFormat::RGBA8:
					AttachColorTexture(_mColorAttachments[i], _mFrameBufferSpec.samples, GL_RGBA8,GL_RGBA, _mFrameBufferSpec.width, _mFrameBufferSpec.height, i);
					break;
				case FrameBufferTextureFormat::RED_INTEGER:
					AttachColorTexture(_mColorAttachments[i], _mFrameBufferSpec.samples, GL_R32I, GL_RED_INTEGER, _mFrameBufferSpec.width, _mFrameBufferSpec.height, i);
					break;
				}
			}
		} 
		if (_mDepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None)
		{
			CreateTextures(multisample, &_mDepthAttachment, 1);
			BindTexture(multisample, _mDepthAttachment);
			switch (_mDepthAttachmentSpecification.TextureFormat)
			{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(_mDepthAttachment, _mFrameBufferSpec.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, _mFrameBufferSpec.width, _mFrameBufferSpec.height);
				break;
			}
		}
		if (_mColorAttachments.size() > 1)
		{
			FPL_CORE_ASSERT("Can't have more than 4 attachments",_mColorAttachments.size() <= 4);
			GLenum  buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(_mColorAttachments.size(), buffers);
		}
		else if(_mColorAttachments.empty())
		{
			glDrawBuffer(GL_NONE);
		}
	
		
		FPL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}