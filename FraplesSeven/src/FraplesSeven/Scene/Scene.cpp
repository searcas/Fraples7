#include "FplPCH.h"
#include "Scene.h"
#include "Component.h"
#include "../Renderer/Renderer2D.h"
#include "Entity.h"
namespace Fraples 
{
	Scene::~Scene()
	{
	}

	void Scene::OnUpdateEngine(TimeSteps ts, EngineCamera& camera)
	{
		Renderer2D::BeginScene(camera);
		auto group = _mRegistry.group<TransformComponent, SpriteRendererComponent>();
		for (auto& entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}
		Renderer2D::EndScene();
	}
	void Scene::OnUpdateRuntime(TimeSteps ts)
	{
		//Update Script
		{
			_mRegistry.view<NativeScriptComponent>().each( [=](auto entity, auto& nativeScriptController) 
			{
					
				if (!nativeScriptController.instance)
				{
					nativeScriptController.instance = nativeScriptController.InstantiateScript();
					nativeScriptController.instance->_mEntity = { entity, this };
					nativeScriptController.instance->OnCreate();
				}
				nativeScriptController.instance->OnUpdate(ts); 
			});
		}
		SceneCamera* mainCam = nullptr;
		glm::mat4 camTransform;
		{
			auto view = _mRegistry.view<TransformComponent, CameraComponent>();
			for (auto& entity : view)
			{
				auto[transfrom, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.mainCamera)
				{
					camTransform = transfrom.GetTransform();
					mainCam = &camera.camera;
					break;
				}
			}
		}
		if (mainCam)
		{
			Renderer2D::BeginScene( Camera(mainCam->GetProjection()) , camTransform );
			auto group = _mRegistry.group<TransformComponent, SpriteRendererComponent>();
			for (auto& entity : group)
			{
				auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}
			Renderer2D::EndScene();
		}
	}
	void Scene::OnViewPortResize(uint32_t width, uint32_t height)
	{
		_mViewPortWidth = width;
		_mViewPortHeight = height;

		auto view = _mRegistry.view<CameraComponent>();
		for (auto& entity : view)
		{
			auto& camComp = view.get<CameraComponent>(entity);
			if (!camComp.fixedAspectRatio)
			{
				camComp.camera.SetViewPortSize(width, height);
			}
		}

	}
	void Scene::DestroyEntity(Entity entity)
	{
		_mRegistry.destroy(entity);
	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { _mRegistry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		if (name.empty())
			tag.tag = "Entity";
		else tag.tag = name;
		return entity;
	}
	Entity Scene::GetMainCameraEntity()
	{
		auto view = _mRegistry.view<CameraComponent>();
		for (auto& entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.mainCamera)
			{
				return Entity{ entity, this };
			}
			return { };
		}
	}
	template <typename T>
	void Scene::OnComponentAdded(Entity entity, T& comopent)
	{
		static_assert(false);
	}
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity,TransformComponent& comp)
	{

	}
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& comp)
	{
		comp.camera.SetViewPortSize(_mViewPortWidth, _mViewPortHeight);
	}
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& comp)
	{

	}
	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& comp)
	{

	}
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& comp)
	{

	}
}