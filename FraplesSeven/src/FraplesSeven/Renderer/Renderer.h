 #pragma once


namespace Fraples
{
	enum class RendererAPI
	{
		NONE		= 0,
		OpenGL		= 1,
		DirectX3D,
		Vulkan,
	};
	class Renderer
	{
	public:
		inline static RendererAPI GetRendererAPI() { return _sRendererAPI; }
	private:
		static RendererAPI _sRendererAPI;
	};
	
}