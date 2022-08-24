#pragma once
#include "../Renderer/Camera.h"

namespace Fraples
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType
		{
			Perspective  = 0,
			Orthographic = 1
		};
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		void SetViewPortSize(uint32_t width, uint32_t height);
// ################# Orthographic #################
		void SetOrthograpihc(float size, float nearClip, float farClip);
		float GetOrthographicSize() const { return _mOrthographicSize; }
		float GetOrthographicNearClip() const { return _mOrthograhpicNear; }
		float GetOrthographicFarClip() const { return _mOrthograhpicFar; }
		void SetOrthographicNearClip(float set) { _mOrthograhpicNear = set; RecalculateProjection(); }
		void SetOrthographicFarClip(float set) { _mOrthograhpicFar = set; RecalculateProjection(); }
		void SetOrthographicSize(float orthographicSize) { _mOrthographicSize = orthographicSize; RecalculateProjection(); }
// ################# Orthographic End #################
		void SetPerspective(float verticalFov, float nearClip, float farClip);
		float GetPerspectiveVerticalFOV() const { return _mPerspectiveFOV; }
		float GetPerspectiveNearClip() const { return _mPerspectiveNear; }
		float GetPerspectiveFarClip() const { return _mPerspectiveFar; }
		void SetPerspectiveNearClip(float set) { _mPerspectiveNear = set; RecalculateProjection(); }
		void SetPerspectiveFarClip(float set) { _mPerspectiveFar = set; RecalculateProjection(); }
		void SetPerspectiveVerticalFOV(float set) { _mPerspectiveFOV = set; RecalculateProjection(); }
// ################# Perspective #################

		const ProjectionType& GetProjectionType() { return _mProjectionType; }
		void SetProjectionType(ProjectionType type) { _mProjectionType = type; RecalculateProjection(); }

	private:
		void RecalculateProjection();
	private:
		float _mOrthographicSize = 10.0f;
		float _mOrthograhpicNear = - 1.0f;
		float _mOrthograhpicFar = 1.0f;

		float _mPerspectiveFOV = glm::radians(45.0f);
		float _mPerspectiveNear = 0.1f;
		float _mPerspectiveFar = 1000.0f;

		float _mAspectRatio = 0.0f;

		ProjectionType _mProjectionType = ProjectionType::Perspective;
	};
} 
