#include "FplPCH.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fraples
{
	Renderer::SceneData* Renderer::_sSceneData = new Renderer::SceneData();
	 
	void Renderer::Init()
	{
		RenderCommands::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		_sSceneData->viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VA, const glm::mat4& transform )
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("_uViewProjectionMatrix", _sSceneData->viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("_uTransform", transform);
		VA->Bind();
		RenderCommands::DrawIndexed(VA);
	}
}