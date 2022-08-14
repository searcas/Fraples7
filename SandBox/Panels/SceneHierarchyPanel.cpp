#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <glm/gtc/type_ptr.hpp>
#include "FraplesSeven/Scene/Component.h" 
namespace Fraples
{
	SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& scene)
	{
		SetScene(scene);
	}
	void SceneHierarchyPanel::SetScene(const std::shared_ptr<Scene>& scene)
	{
		_mScene = scene;
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		_mScene->_mRegistry.each([this](auto& entityID)
			{
				Entity entity{ entityID, _mScene.get() };
				DrawEntityNode(entity);
			});
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			_mSceneSelection = {};
		ImGui::End();


		ImGui::Begin("Properties");
		if (_mSceneSelection)
		{
			DrawComponents(_mSceneSelection);
		}

		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;
		ImGuiTreeNodeFlags flags = ((_mSceneSelection == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			_mSceneSelection = entity;
		}
		if (opened)
		{
			ImGui::TreePop();
		}
	}
	static void DrawVec3Control(const char* label, glm::vec3& values, float speed = 0.1f, float resetValue = 0.0f, float columnWidth = 100.0f )
	{
		ImGui::PushID(label);
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();


		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		float lineheight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize{ lineheight + 3.0f, lineheight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0, 0.3, 0.3, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.8f, 0.1, 0.1, 0.3f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0, 0.9, 0.9, 1.0f });
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1,1.0,0.3,0.8f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.0f,0.2,1.0,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0,0.9,0.9,1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, speed);
		ImGui::PopItemWidth();
		ImGui::SameLine();


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.3,0.2,1.0,0.6f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 1.0f,0.2,0.2,1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 1.0,0.9,0.9,1.0f });
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, speed);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transformComponent = entity.GetComponent<TransformComponent>();
				DrawVec3Control("Translation", transformComponent.Translation);
				glm::vec3 rotation = glm::degrees(transformComponent.Rotation);
				DrawVec3Control("Rotation", rotation,1.0f);
				transformComponent.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", transformComponent.Scale,1.0f);
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.camera;

				ImGui::Checkbox("Primary", &cameraComponent.mainCamera);

				const char* projectionTypeStrings[] = { "Perspective","Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[static_cast<int>(camera.GetProjectionType())];

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (size_t i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							cameraComponent.camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}
						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					{
						float orthoSize = camera.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &orthoSize))
							camera.SetOrthographicSize(orthoSize);
					}
					{
						float orthoNear = camera.GetOrthographicNearClip();
						if (ImGui::DragFloat("Near", &orthoNear))
							camera.SetOrthographicNearClip(orthoNear);
					}
					{
						float orthoFar = camera.GetOrthographicFarClip();
						if (ImGui::DragFloat("Far", &orthoFar))
							camera.SetOrthographicFarClip(orthoFar);
					}
					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.fixedAspectRatio);

				}
				else if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					{
						float verticalFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
						if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
							camera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));
					}
					{
						float perpsectiveNear = camera.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near", &perpsectiveNear))
							camera.SetPerspectiveNearClip(perpsectiveNear);
					}
					{
						float perpsectiveFar = camera.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far", &perpsectiveFar))
							camera.SetPerspectiveFarClip(perpsectiveFar);
					}
				}
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
			{
				auto& src = entity.GetComponent<SpriteRendererComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(src.color));
				ImGui::TreePop();
			}
		}
	}
}