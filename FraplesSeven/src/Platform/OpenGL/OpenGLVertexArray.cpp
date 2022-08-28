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
		for (const auto& element : layout)
		{
			switch (element.SDataType)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(_mVertexBufferIndex);
				glVertexAttribPointer(_mVertexBufferIndex, element.GetComponentCount(), 
					ShaderDataTypeToOpenGLBaseType(element.SDataType),
					element.Normalized ? GL_TRUE : GL_FALSE, 
					layout.GetStride(),
					(const void*)element.Offset);
				_mVertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Boolean:
			{
				glEnableVertexAttribArray(_mVertexBufferIndex);
				glVertexAttribIPointer(_mVertexBufferIndex, element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.SDataType),
					layout.GetStride(),
					(const void*)element.Offset);
				_mVertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(_mVertexBufferIndex);
					glVertexAttribPointer(_mVertexBufferIndex, count, ShaderDataTypeToOpenGLBaseType(element.SDataType),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(), (const void*)(sizeof(float) * count * i));
					glVertexAttribDivisor(_mVertexBufferIndex, 1);
					_mVertexBufferIndex++;
				}
				break;
			}
			default:
				FPL_CORE_ASSERT(false, "Unknown ShaderDataType");
			}
			
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

