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
		FPL_CORE_ASSERTS(false, "Unkonwn Shader Type.");

		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &_mRendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_mRendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(_mRendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(_mRendererID);
		vertexBuffer->Bind();

		FPL_CORE_ASSERTS(vertexBuffer->GetLayout().GetElements().size()," Vertex Buffer has no layout");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& elements : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, elements.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(elements.SDataType), elements.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)elements.Offset);
			index++;
		}
		_mVertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(_mRendererID);
		indexBuffer->Bind();

		_mIndexBuffer = indexBuffer;
	}



}
