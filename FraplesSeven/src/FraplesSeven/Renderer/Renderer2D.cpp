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
		std::shared_ptr<Shader>textureShader;
		std::shared_ptr<Texture2D> WhiteTexture;
	};
	static Renderer2DStorage* _sData;

	void Renderer2D::Init()
	{
		FPL_PROFILE_FUNCTION();
		_sData = new Renderer2DStorage;
		_sData->QuadVertexArray = Fraples::VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,	0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,	0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Fraples::VertexBuffer>squareVBuffer;
		squareVBuffer.reset(Fraples::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVBuffer->SetLayout({ {Fraples::ShaderDataType::Float3, "_aPosition"},{Fraples::ShaderDataType::Float2, "_aTexCoord"} });
		_sData->QuadVertexArray->AddVertexBuffer(squareVBuffer);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fraples::IndexBuffer>squareIBuffer;
		squareIBuffer.reset(Fraples::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_sData->QuadVertexArray->SetIndexBuffer(squareIBuffer);

		_sData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		_sData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		_sData->textureShader   = Fraples::Shader::Create("assets/Shaders/Texture.glsl");
		_sData->textureShader->Bind();
		_sData->textureShader->SetUniformInt("_uTexture", 0);
	}
	void Renderer2D::BeginScene(const Fraples::OrthographicCamera& orthoCam)
	{
		FPL_PROFILE_FUNCTION();
		_sData->textureShader->Bind();
		_sData->textureShader->SetUniformMat4("_uViewProjectionMatrix", orthoCam.GetViewProjectionMatrix());

	}
	void Renderer2D::EndScene()
	{
		FPL_PROFILE_FUNCTION();

	}
	void Renderer2D::ShutDown()
	{
		FPL_PROFILE_FUNCTION();
		delete _sData;
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		FPL_PROFILE_FUNCTION();
		_sData->textureShader->SetUniformFloat4("_uColor", color);
		_sData->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		_sData->textureShader->SetUniformMat4("_uTransform", transform);

		_sData->QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData->QuadVertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
	{
		FPL_PROFILE_FUNCTION();
		DrawQuad({ position.x,position.y, 0.0f }, size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
	{
		_sData->textureShader->SetUniformFloat4("_uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		_sData->textureShader->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y, 1.0f });
		_sData->textureShader->SetUniformMat4("_uTransform", transform);

		texture->Bind();
		_sData->QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData->QuadVertexArray);

	}
}