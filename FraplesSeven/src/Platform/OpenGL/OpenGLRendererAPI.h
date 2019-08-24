#pragma once

#include "FraplesSeven/Renderer/RendererAPI.h"


namespace Fraples
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VA) override;
	};
}