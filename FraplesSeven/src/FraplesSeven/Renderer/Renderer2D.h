#pragma once
#include "OrthographicCamera.h"
#include "Texture.h"
namespace Fraples{
	
	class Renderer2D {
	
public:
	
	static void Init();
	static void BeginScene(const Fraples::OrthographicCamera& orthoCam);
	static void EndScene();
	
	static void ShutDown();
	
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawQuadRotation(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawQuadRotation(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawQuadRotation(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 & tintColor = glm::vec4(1.0f));
	static void DrawQuadRotation(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 & tintColor = glm::vec4(1.0f));

private:
	

	
	};
}