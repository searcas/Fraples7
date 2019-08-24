#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Fraples
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OpenGL = 1,
			DirectX3D,
			Vulkan,
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VA) = 0;
		inline static API getAPI(){ return _sAPI; }
	private:
		static API _sAPI;
	};
}