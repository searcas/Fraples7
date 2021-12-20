#pragma once
#include "FraplesSeven/Renderer/OrthographicCamera.h"
#include "FraplesSeven/Core/TimeSteps.h"

#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/Events/MouseEvent.h"

namespace Fraples
{
	struct OrthographicCameraBounds
	{
		float left, right;
		float bottom, top;

		float GetWidth() { return right - left; }
		float GetHeight() { return top - bottom; }

	};
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeSteps ts);
		void OnEvent(Event& ev);
		 const OrthographicCamera& GetCamera() const { return _mOrthoCam; }
		 OrthographicCamera& GetCamera() { return _mOrthoCam; }

		 void SetZoomLevel(float level) { _mZoomLevel = level; CalculateView(); }
		float GetZoomLevel() { return _mZoomLevel; }

		const OrthographicCameraBounds& GetBounds() const { return _mBounds; }
		
	private:
		void CalculateView();
		bool OnMouseScrolled(MouseScrollEvent& ev);
		bool OnWindowResize(WindowResizeEvent& ev);
	private:
		float _mAspectRatio;
		float _mZoomLevel = 1.0f;
		OrthographicCameraBounds _mBounds;
		OrthographicCamera _mOrthoCam;
		
		
		bool _mRotation;

		glm::vec3 _mCameraPosition = { 0.0f,0.0f,0.0f };
		float _mCameraRotation = 0.0f;
		float _mCameraTranslationSpeed = 1.0f;
		float _mCameraRotationSpeed = 180.5f;

	};
}


