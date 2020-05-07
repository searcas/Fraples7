#pragma once
#include "RendererAPI.h"


namespace Fraples
{
	class RenderCommands {
	public:
		inline static void Init()
		{
			_sRendererAPI->Init();
		}
		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			_sRendererAPI->SetViewPort(x, y, width, height);
		}
		inline static void SetClearColor(const glm::vec4& color) 
		{
			_sRendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			_sRendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>&VA, uint32_t count = 0)
		{
			_sRendererAPI->DrawIndexed(VA, count);
		}
	
	private:
		static RendererAPI* _sRendererAPI;
	};
}