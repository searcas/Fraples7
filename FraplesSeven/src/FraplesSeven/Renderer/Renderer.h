 #pragma once
#include "RenderCommands.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace Fraples
{
	
	class Renderer
	{
	public:
		//TODO
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VA, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::getAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};
		static SceneData* _sSceneData;
	};
	
}