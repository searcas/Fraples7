#pragma once
#include "FrameBuffer.h"
#include "FraplesSeven/Core/Core.h"

namespace Fraples
{
	struct FrameBufferSpec
	{
		uint32_t width;
		uint32_t height;
		uint32_t samples = 1;

		bool SwapChainTarget = false;

	};
	class FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual const FrameBufferSpec& GetFrameBufferSpec() = 0;
		static shared<FrameBuffer>Create(const FrameBufferSpec& spec);
	private:
	};
}