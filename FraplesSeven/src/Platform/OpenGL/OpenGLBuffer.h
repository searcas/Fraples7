#pragma once

#include "FraplesSeven/Renderer/Buffer.h"

namespace Fraples
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;

		inline virtual const BufferLayout& GetLayout() const override { return _mLayout; }
		inline virtual void SetLayout(const BufferLayout& layout) override { _mLayout = layout; }

	private:
		uint32_t _mRendererID;
		BufferLayout _mLayout;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()const override;
		virtual void Unbind()const override;
		inline virtual uint32_t GetCount()const { return _mCount; }
	private:
		uint32_t _mRendererID;
		uint32_t _mCount;
	};
}