#include "FplPCH.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


namespace Fraples{


	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &_mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &_mRendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	//#######################################################################
	//INDEX BUFFER
	//#######################################################################
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) :_mCount(count)
	{
		glCreateBuffers(1, &_mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &_mRendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mRendererID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}