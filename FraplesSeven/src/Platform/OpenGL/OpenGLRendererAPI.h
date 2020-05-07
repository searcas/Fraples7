#pragma once

#include "FraplesSeven/Renderer/RendererAPI.h"


namespace Fraples
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Init() override;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VA, uint32_t indexCount = 0) override;
	};
}