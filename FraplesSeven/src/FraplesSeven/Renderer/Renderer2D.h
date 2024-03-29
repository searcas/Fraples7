#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "Camera.h"
#include "EngineCamera.h"
namespace Fraples{
	
	class Renderer2D {
public:
	static void Init();
	static void BeginScene(Camera& camera, const glm::mat4& transform);
	static void BeginScene(const Fraples::EngineCamera& orthoCam);
	static void BeginScene(const Fraples::OrthographicCamera& orthoCam);
	static void EndScene();
	static void Flush();

	static void ShutDown();
	

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& Texture, float tiling = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);
	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f), int entityID = -1);


	static void RenderRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void RenderRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void RenderRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 & tintColor = glm::vec4(1.0f));
	static void RenderRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 & tintColor = glm::vec4(1.0f));

	static void DrawSprite(const glm::mat4& transform, class SpriteRendererComponent& sprite, int entityID);

	struct Statistics
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCounts = 0;
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		uint32_t GetTotalVertexCount() { return QuadCounts * 4; };
		uint32_t GetTotalIndexCount() { return QuadCounts * 6; };
		glm::vec3 GetPosition() { return Position; }
	};
	static Statistics GetStats();
	static void ResetStats();
	static void FlushAndReset();
	};
}