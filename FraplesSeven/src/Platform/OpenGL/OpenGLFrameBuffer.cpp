#include "FplPCH.h"
#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"

namespace Fraples
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec& spec) :
		_mFrameBufferSpec(spec)
	{
		Validate();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &_mRendererID);
	}
	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _mRendererID); 
	}
	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::Validate()
	{
		glCreateFramebuffers(1, &_mRendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, _mRendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &_mColorAttach);  
 		glBindTexture(GL_TEXTURE_2D, _mColorAttach);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _mFrameBufferSpec.width, _mFrameBufferSpec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _mColorAttach, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &_mDepthAttach);
		glBindTexture(GL_TEXTURE_2D, _mDepthAttach);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _mFrameBufferSpec.width, _mFrameBufferSpec.height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8,_mFrameBufferSpec.width, _mFrameBufferSpec.height,0 ,GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _mDepthAttach, 0);

		FPL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}