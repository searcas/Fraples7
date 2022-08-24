#include "FplPCH.h"
#include "EngineCamera.h"
#include "FraplesSeven/Core/Input.h"
#include "glm/gtx/quaternion.hpp"	
namespace Fraples
{
	EngineCamera::EngineCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:_mFOV(fov), _mAspectRatio(aspectRatio), _mNearClip(nearClip), _mFarClip(farClip),
		Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		UpdateView();
	}
	void EngineCamera::UpdateProjection()
	{
		_mAspectRatio = _mViewportWidth / _mViewportHeight;
		_mProjection = glm::perspective(glm::radians(_mFOV), _mAspectRatio, _mNearClip, _mFarClip);
	}
	void EngineCamera::UpdateView()
	{
		//_mYaw = _mPitch = 0.0f; // lock the camera's rotation
		_mPosition = CalculatePosition();
	
		glm::quat orientation = GetOrientation();
		_mViewMatrix = glm::translate(glm::mat4(1.0f), _mPosition) * glm::mat4(orientation);
		if (Input::IsKeyPressed(Key::W))
		{
			_mViewMatrix[3].y += 30;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			_mViewMatrix[3].y -= 30;
		}
		if (Input::IsKeyPressed(Key::A))
		{
			_mViewMatrix[3].x -= 30;

		}
		else if (Input::IsKeyPressed(Key::D))
		{
			_mViewMatrix[3].x += 30;
		}
		_mViewMatrix = glm::inverse(_mViewMatrix);
	}
	std::pair<float, float>EngineCamera::PanSpeed() const
	{
		float x = std::min(_mViewportWidth / 1000.0f, 2.4f); //max = 2.4f
		float xFactor = 0.0367f * (x * x) - 0.17778 * x + 0.3021f;

		float y = std::min(_mViewportWidth / 1000.0f, 2.4f); //max = 2.4f
		float yFactor = 0.0367f * (y * y) - 0.17778 * y + 0.3021f;
		return { xFactor, yFactor };
	}
	float EngineCamera::ZoomSpeed() const
	{
		float distance = _mDistance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); //max speed = 100

		return speed;
	}
	void EngineCamera::OnUpdate(const TimeSteps& ts)
	{
		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - _mInitialMousePosition) * 0.003f;
			_mInitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);

		}
	
		UpdateView();
	}
	void EngineCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrollEvent>(FPL_BIND_EVENT_FN(EngineCamera::OnMouseScroll));
	}
	bool EngineCamera::OnMouseScroll(MouseScrollEvent& e)
	{
		float delta = e.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}
	void EngineCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		_mFocalPoint += -GetRightDirection() * delta.x * xSpeed * _mDistance;
		_mFocalPoint += GetUpDirection() * delta.y * ySpeed * _mDistance;
	}
	void EngineCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		_mYaw += yawSign * delta.x * RotationSpeed();
		_mPitch += delta.y * RotationSpeed();
	}
	void EngineCamera::MouseZoom(float delta)
	{
		_mDistance -= delta * ZoomSpeed();
		if (_mDistance < 1.0f)
		{
			_mFocalPoint += GetForwardDirection();
			_mDistance = 1.0f;
		}
	}
	glm::vec3 EngineCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	glm::vec3 EngineCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	glm::vec3 EngineCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}
	glm::vec3 EngineCamera::CalculatePosition() const
	{
		return _mFocalPoint - GetForwardDirection() * _mDistance;
	}
	glm::quat EngineCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-_mPitch, -_mYaw, 0.0f));
	}
}