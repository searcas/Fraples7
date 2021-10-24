#include "FplPCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommands.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Fraples
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

		float TexIndex;
		float Tilling;
	};
	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		
		static constexpr uint32_t MaxTextureSlots = 32;
		 
		std::shared_ptr<VertexArray>QuadVertexArray;
		std::shared_ptr<VertexBuffer>QuadVertexBuffer;

		std::shared_ptr<Shader>TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		
		std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;
	};


	static Renderer2DData _sData;

	void Renderer2D::Init()
	{
		FPL_PROFILE_FUNCTION();
		_sData.QuadVertexArray = VertexArray::Create();

		_sData.QuadVertexBuffer = VertexBuffer::Create(_sData.MaxVertices * sizeof(QuadVertex));

		_sData.QuadVertexBuffer->SetLayout({

			{ Fraples::ShaderDataType::Float3, "_aPosition"},
		
			{ Fraples::ShaderDataType::Float4, "_aColor"},

			{ Fraples::ShaderDataType::Float2, "_aTexCoord"},

			{ Fraples::ShaderDataType::Float, "_aTexIndex"},
		
			{ Fraples::ShaderDataType::Float, "_aTiling"}

		});
		_sData.QuadVertexArray->AddVertexBuffer(_sData.QuadVertexBuffer);
		_sData.QuadVertexBufferBase = new QuadVertex[_sData.MaxVertices];

		uint32_t* quadIndices = new uint32_t[_sData.MaxIndices];
		uint32_t offset = 0;

		for (uint32_t i = 0; i < _sData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		std::shared_ptr<IndexBuffer>quadIndexBuffer = IndexBuffer::Create(quadIndices, _sData.MaxIndices);
		_sData.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		_sData.WhiteTexture = Texture2D::Create(1, 1);
		 uint32_t whiteTextureData = 0xffffffff;
		_sData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		int32_t samplers[_sData.MaxTextureSlots];
		for (uint32_t i = 0; i < _sData.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}
		_sData.TextureShader = Fraples::Shader::Create("assets/Shaders/Texture.glsl");
		_sData.TextureShader->Bind();
		_sData.TextureShader->SetIntArray("_uTextures", samplers, _sData.MaxTextureSlots);
		_sData.TextureSlots[0] = _sData.WhiteTexture;
	}
	void Renderer2D::BeginScene(const Fraples::OrthographicCamera& orthoCam)
	{
		FPL_PROFILE_FUNCTION();
		_sData.TextureShader->Bind();
		_sData.TextureShader->SetUniformMat4("_uViewProjectionMatrix", orthoCam.GetViewProjectionMatrix());
		 
		_sData.QuadIndexCount = 0;
		_sData.QuadVertexBufferPtr = _sData.QuadVertexBufferBase;
		_sData.TextureSlotIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		FPL_PROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)_sData.QuadVertexBufferPtr - (uint8_t*)_sData.QuadVertexBufferBase;
		_sData.QuadVertexBuffer->SetData(_sData.QuadVertexBufferBase, dataSize);
		
		Flush();
	}
	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < _sData.TextureSlotIndex; i++)
		{
			_sData.TextureSlots[i]->Bind(i);
		}
		RenderCommands::DrawIndexed(_sData.QuadVertexArray, _sData.QuadIndexCount);
	}
	void Renderer2D::ShutDown()
	{
		FPL_PROFILE_FUNCTION();
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x,position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		FPL_PROFILE_FUNCTION();
		constexpr float texIndex = 0.0f; //White Texture
		constexpr float tiling = 1.0f; 
		_sData.QuadVertexBufferPtr->Position = position;
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 0.0f,0.0f };
		_sData.QuadVertexBufferPtr->TexIndex = texIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = {position.x + size.x, position.y, 0.0f};
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		_sData.QuadVertexBufferPtr->TexIndex = texIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		_sData.QuadVertexBufferPtr->TexIndex = texIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		_sData.QuadVertexBufferPtr->TexIndex = texIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadIndexCount += 6;
		/*
		_sData.TextureShader->SetUniformFloat("_uTiling", 1.0f);
		_sData.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		_sData.TextureShader->SetUniformMat4("_uTransform", transform);

		_sData.QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData.QuadVertexArray);
		*/
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		FPL_PROFILE_FUNCTION();
		DrawQuad({ position.x,position.y, 0.0f }, size, texture, tiling, tintColor);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		FPL_PROFILE_FUNCTION();
		
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < _sData.TextureSlotIndex; i++)
		{
			if (*_sData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)_sData.TextureSlotIndex;
			_sData.TextureSlots[_sData.TextureSlotIndex] = texture;
			_sData.TextureSlotIndex++;
		}

		_sData.QuadVertexBufferPtr->Position = position;
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		_sData.QuadVertexBufferPtr->TexIndex = textureIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		_sData.QuadVertexBufferPtr->TexIndex = textureIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		_sData.QuadVertexBufferPtr->TexIndex = textureIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		_sData.QuadVertexBufferPtr->Color = color;
		_sData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		_sData.QuadVertexBufferPtr->TexIndex = textureIndex;
		_sData.QuadVertexBufferPtr->Tilling = tiling;
		_sData.QuadVertexBufferPtr++;

		_sData.QuadIndexCount += 6;

#if 0
		_sData.TextureShader->SetUniformFloat4("_uColor", tintColor);
		_sData.TextureShader->SetUniformFloat("_uTiling", tiling);

		_sData.TextureShader->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y, 1.0f });
		_sData.TextureShader->SetUniformMat4("_uTransform", transform);

		texture->Bind();
		_sData.QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData.QuadVertexArray);
#endif

	}
	void Renderer2D::DrawQuadRotation(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuadRotation({ position.x, position.y, 0.0f }, size, rotation,color);

	}
	void Renderer2D::DrawQuadRotation(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		FPL_PROFILE_FUNCTION();
		_sData.TextureShader->SetUniformFloat4("_uColor", color);
		_sData.TextureShader->SetUniformFloat("_uTiling", 1.0f);
		_sData.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		_sData.TextureShader->SetUniformMat4("_uTransform", transform);

		_sData.QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData.QuadVertexArray);
	}
	void Renderer2D::DrawQuadRotation(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		FPL_PROFILE_FUNCTION();
		DrawQuadRotation({ position.x,position.y, 0.0f }, size, rotation, texture, tiling, tintColor);
	}
	void Renderer2D::DrawQuadRotation(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		_sData.TextureShader->SetUniformFloat4("_uColor", tintColor);
		_sData.TextureShader->SetUniformFloat("_uTiling", tiling);

		_sData.TextureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) 
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		_sData.TextureShader->SetUniformMat4("_uTransform", transform);

		texture->Bind();
		_sData.QuadVertexArray->Bind();
		RenderCommands::DrawIndexed(_sData.QuadVertexArray);
	}
}