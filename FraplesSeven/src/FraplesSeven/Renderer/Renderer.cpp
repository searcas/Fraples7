#include "FplPCH.h"
#include "Renderer.h"


namespace Fraples
{
	Renderer::SceneData* Renderer::_sSceneData = new Renderer::SceneData();
	 
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		_sSceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VA)
	{
		shader->Bind();
		shader->UploadUniformMat4("_uViewProjectionMatrix", _sSceneData->viewProjectionMatrix);
		VA->Bind();
		RenderCommands::DrawIndexed(VA);
	}
}