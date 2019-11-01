#include "FplPCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommands.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Fraples
{
	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray>QuadVertexArray;
		std::shared_ptr<Shader>flatColorShader;

	};
	static Renderer2DStorage* _sData;

	void Renderer2D::Init()
	{
		_sData = new Renderer2DStorage;
			_sData->QuadVertexArray = Fraples::VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,	0.5f, 0.0f,
			-0.5f,	0.5f, 0.0f
		};

		std::shared_ptr<Fraples::VertexBuffer>squareVBuffer;
		squareVBuffer.reset(Fraples::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVBuffer->SetLayout({ {Fraples::ShaderDataType::Float3, "_aPosition"} });
		_sData->QuadVertexArray->AddVertexBuffer(squareVBuffer);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fraples::IndexBuffer>squareIBuffer;
		squareIBuffer.reset(Fraples::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_sData->QuadVertexArray->SetIndexBuffer(squareIBuffer);


		_sData->flatColorShader = Fraples::Shader::Create("assets/Shaders/FlatColor.glsl");
	}
	void Renderer2D::BeginScene(const Fraples::OrthographicCamera& orthoCam)
	{
		_sData->flatColorShader->Bind();
		_sData->flatColorShader->SetUniformMat4("_uViewProjectionMatrix", orthoCam.GetViewProjectionMatrix());

	}
	void Renderer2D::EndScene()
	{

	}
	void Renderer2D::ShutDown()
	{
		delete _sData;

	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y,0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		_sData->flatColorShader->Bind();
		_sData->flatColorShader->SetUniformFloat4("_uColor", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		_sData->flatColorShader->SetUniformMat4("_uTransform", transform);
		_sData->QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData->QuadVertexArray);
	}
}