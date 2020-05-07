#include "FplPCH.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"


namespace Fraples{
	//#######################################################################
	//Vertex Buffer
	//#######################################################################

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		FPL_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &_mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		FPL_PROFILE_FUNCTION();

		glCreateBuffers(1, &_mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		FPL_PROFILE_FUNCTION();
		glDeleteBuffers(1, &_mRendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	//#######################################################################
	//Index Buffer
	//#######################################################################
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) :_mCount(count)
	{
		FPL_PROFILE_FUNCTION();
		glCreateBuffers(1, &_mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _mRendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		FPL_PROFILE_FUNCTION();
		glDeleteBuffers(1, &_mRendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mRendererID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}