#pragma once
#include "glm/glm.hpp"
#include "Camera.h"
#include "FraplesSeven/Core/TimeSteps.h"
#include "FraplesSeven/Events/MouseEvent.h"

namespace Fraples
{
	class EngineCamera : public Camera
	{
	public:
		EngineCamera() = default;
		EngineCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(const TimeSteps& ts);
		void OnEvent(Event& e);

		float GetDistance()const { return _mDistance; }
		void GetDistance(float distance ){ _mDistance = distance; }

		void SetViewportSize(float width, float height) { _mViewportWidth = width; _mViewportHeight = height; UpdateProjection(); }
		
		const glm::mat4& GetViewMatrix() const { return _mViewMatrix; }
		glm::mat4 GetViewProjection()const { return _mProjection * _mViewMatrix; }

		glm::vec3 GetUpDirection()const;
		glm::vec3 GetRightDirection()const;
		glm::vec3 GetForwardDirection()const;
		
		const glm::vec3& GetPosition() const { return _mPosition; }
		glm::quat GetOrientation()const;

		float GetPitch()const { return _mPitch; }
		float GetYaw()const { return _mYaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrollEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition()const;
		std::pair<float, float>PanSpeed()const;
		float RotationSpeed() const { return 0.869f; }
		float ZoomSpeed()const;
	private:
		float _mFOV = 45.0f, _mAspectRatio = 1.778f, _mNearClip = 0.1f, _mFarClip = 1000.0f;

		glm::mat4 _mViewMatrix;
		glm::vec3 _mPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _mFocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 _mInitialMousePosition;

		float _mDistance = 10.0f;
		float _mPitch = 0.0f, _mYaw = 0.0f;
		
		float _mViewportWidth = 1280, _mViewportHeight = 720;

	};
}
