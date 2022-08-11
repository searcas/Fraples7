#pragma once
#include "glm/glm.hpp"
#include "SceneCamera.h"


namespace Fraples
{
	class SceneCamera;
	struct TagComponent
	{
		std::string tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : tag(tag) {}
	};
	struct TransformComponent
	{
		glm::mat4 _mTransform {1.0f};
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transfrom) : _mTransform(transfrom) {}
		operator const glm::mat4& () { return _mTransform; }
		operator glm::mat4& () { return _mTransform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color{ 1.0f,1.0f,1.0f,1.0f };
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& Color) : color(Color) {}
		operator const glm::vec4& () { return color; }
		operator glm::vec4& () { return color; }
	};

	struct CameraComponent
	{
		SceneCamera camera; 
		bool mainCamera = true;
		bool fixedAspectRatio = false;
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

	};
}