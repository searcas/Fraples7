#include "FplPCH.h"

#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Fraples
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Fraples::ShaderDataType::Float:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float2:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float3:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float4:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Int:
			return GL_INT;
		case Fraples::ShaderDataType::Int2:
			return GL_INT;
		case Fraples::ShaderDataType::Int3:
			return GL_INT;
		case Fraples::ShaderDataType::Int4:
			return GL_INT;
		case Fraples::ShaderDataType::Boolean:
			return GL_BOOL;
		default:
			break;
		}
		FPL_CORE_ASSERT(false, "Unkonwn Shader Type.");

		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		FPL_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &_mRendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		FPL_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &_mRendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindVertexArray(_mRendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		FPL_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		FPL_PROFILE_FUNCTION();
		glBindVertexArray(_mRendererID);
		vertexBuffer->Bind();

		FPL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size()," Vertex Buffer has no layout");

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& elements : layout)
		{
			glEnableVertexAttribArray(_mVertexBufferIndex);
			glVertexAttribPointer( _mVertexBufferIndex, elements.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(elements.SDataType), elements.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)(intptr_t)elements.Offset);
			_mVertexBufferIndex++;
		}
		_mVertexBuffer.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		FPL_PROFILE_FUNCTION();
		glBindVertexArray(_mRendererID);
		indexBuffer->Bind();

		_mIndexBuffer = indexBuffer;
	}



}

