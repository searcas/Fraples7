#pragma once
#include "OrthographicCamera.h"
 
namespace Fraples{
	
	class Renderer2D {
	
public:
	
	static void Init();
	static void BeginScene(const Fraples::OrthographicCamera& orthoCam);
	static void EndScene();
	
	static void ShutDown();
	
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	
private:
	

	
	};
}