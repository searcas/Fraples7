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
		inline static void SetClearColor(const glm::vec4& color) 
		{
			_sRendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			_sRendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>&VA)
		{
			_sRendererAPI->DrawIndexed(VA);
		}
	
	private:
		static RendererAPI* _sRendererAPI;
	};
}