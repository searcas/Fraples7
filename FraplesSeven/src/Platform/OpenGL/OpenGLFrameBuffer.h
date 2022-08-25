#pragma once
#include "FraplesSeven/Renderer/FrameBuffer.h"

namespace Fraples
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();
		virtual void Bind() override;
		virtual void Unbind() override; 
		virtual const FrameBufferSpec& GetFrameBufferSpec() override { return _mFrameBufferSpec; }
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const { 
			FPL_CORE_ASSERT("Index should be less than ColorAttachmentSize", index < _mColorAttachments.size()); return _mColorAttachments[index]; }
		virtual void Resize(uint32_t width, uint32_t height) override;

		void Validate();
	private:
		FrameBufferSpec _mFrameBufferSpec;
		uint32_t _mRendererID = 0;

		std::vector<FrameBufferTextureSpecification>_mColorAttachmentSpecification;
		FrameBufferTextureSpecification _mDepthAttachmentSpecification = FrameBufferTextureFormat::None;
		std::vector<uint32_t>_mColorAttachments;
		uint32_t _mDepthAttachment = 0;
	};

}