#pragma once
#include "FrameBuffer.h"
#include "FraplesSeven/Core/Core.h"

namespace Fraples
{
	enum class FrameBufferTextureFormat
	{
		None = 0,
		// color
		RGBA8,

		// Depth/Stencil
		DEPTH24STENCIL8,

		// Defualts
		Depth = DEPTH24STENCIL8
	};
	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format) {} 

		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
	};
	struct FrameBufferAttachmentSpecification
	{
		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments) : Attachments(attachments)
		{}
		
		std::vector<FrameBufferTextureSpecification> Attachments;
	};
	struct FrameBufferSpec
	{
		uint32_t width;
		uint32_t height;
		uint32_t samples = 1;
		FrameBufferAttachmentSpecification Attachments;
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
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0 ;
		virtual const FrameBufferSpec& GetFrameBufferSpec() = 0;
		static shared<FrameBuffer>Create(const FrameBufferSpec& spec);
	private:
	};
}