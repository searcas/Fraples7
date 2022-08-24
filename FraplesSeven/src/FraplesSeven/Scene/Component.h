#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "SceneCamera.h"
#include "FraplesSeven/Core/TimeSteps.h"
#include "ScriptableEntity.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx//quaternion.hpp"

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
		glm::vec3 Translation{ 0.0f };
		glm::vec3 Scale { 1.0f };
		glm::vec3 Rotation { 0.0f };
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform()const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f),Scale);
		}
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
	struct NativeScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent*);


		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nativeScript) {delete nativeScript->instance; nativeScript->instance = nullptr; };
	 	}
	};
}