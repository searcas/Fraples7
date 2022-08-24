#pragma once
#include "entt.hpp"
#include "../Core/TimeSteps.h"
#include "FraplesSeven/Renderer/EngineCamera.h"
namespace Fraples
{

	class Scene
	{
		friend class Entity;
		friend class SceneSerializer;
	public:
		Scene() = default;
		~Scene();
		Entity CreateEntity(const std::string& tag ="");
		void OnUpdateRuntime(TimeSteps ts);
		void OnUpdateEngine(TimeSteps ts, EngineCamera& camera);
		void OnViewPortResize(uint32_t width, uint32_t height);
		void DestroyEntity(Entity entity);
		template <typename T>
		void OnComponentAdded(Entity entity, T& comopent);
		Entity GetMainCameraEntity();
	private:
		entt::registry _mRegistry;  
		uint32_t _mViewPortWidth = 0;
		uint32_t _mViewPortHeight = 0;
		friend class SceneHierarchyPanel;
	};
}