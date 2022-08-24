#pragma once
#include "FraplesSeven/Scene/Scene.h" 
#include "FraplesSeven/Scene/Entity.h" 


namespace Fraples
{
	class Entity;
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::shared_ptr<Scene>& scene);
		void SetScene(const std::shared_ptr<Scene>& scene);
		void OnImGuiRender();
		Entity GetSelectedEntity() const { return _mSceneSelection; };
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		std::shared_ptr<Scene>_mScene;
		Entity _mSceneSelection;
	};
}