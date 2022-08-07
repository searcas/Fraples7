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
		virtual uint32_t GetColorAttachmentRendererID() const { return _mColorAttach; }
		virtual void Resize(uint32_t width, uint32_t height) override;

		void Validate();
	private:
		FrameBufferSpec _mFrameBufferSpec;
		uint32_t _mRendererID = 0;
		uint32_t _mColorAttach = 0;
		uint32_t _mDepthAttach = 0;
	};

}