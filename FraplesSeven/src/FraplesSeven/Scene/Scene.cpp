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
	void Scene::OnUpdate(TimeSteps ts)
	{
		SceneCamera* mainCam = nullptr;
		glm::mat4* camTransform = nullptr;
		{
			auto view = _mRegistry.view<TransformComponent, CameraComponent>();
			for (auto& entity : view)
			{
				auto& [transfrom, camera] = view.get< TransformComponent, CameraComponent>(entity);
				if (camera.mainCamera)
				{
					camTransform = &transfrom._mTransform;
					mainCam = &camera.camera;
					break;
				}
			}
		}
		if (mainCam)
		{
			Renderer2D::BeginScene(Camera{ mainCam->GetProjection() }, *camTransform);
			auto group = _mRegistry.group<TransformComponent, SpriteRendererComponent>();
			for (auto& entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.color);
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
}