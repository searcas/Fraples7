#pragma once

#include "FraplesSeven/Renderer/VertexArray.h"

namespace Fraples
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		inline const std::vector<std::shared_ptr<VertexBuffer>>&GetVertexBuffers()const override{ return _mVertexBuffer; } 
		inline const std::shared_ptr<IndexBuffer>&GetIndexBuffer() const override { return _mIndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>>_mVertexBuffer;
		std::shared_ptr<IndexBuffer>_mIndexBuffer;
		uint32_t _mRendererID;
	};
}