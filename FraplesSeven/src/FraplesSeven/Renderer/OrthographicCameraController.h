#pragma once
#include "FraplesSeven/Renderer/OrthographicCamera.h"
#include "FraplesSeven/Core/TimeSteps.h"

#include "FraplesSeven/Events/AppEvent.h"
#include "FraplesSeven/Events/MouseEvent.h"

namespace Fraples
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeSteps ts);
		void OnEvent(Event& ev);
		inline const OrthographicCamera& GetCamera() const { return _mOrthoCam; }
		inline OrthographicCamera& GetCamera() { return _mOrthoCam; }

		void SetZoomLevel(float level) { _mZoomLevel = level; }
		float GetZoomLevel() { return _mZoomLevel; }
		
	private:
		bool OnMouseScrolled(MouseScrollEvent& ev);
		bool OnWindowResize(WindowResizeEvent& ev);
	private:
		float _mAspectRatio;
		float _mZoomLevel = 1.0f;
		OrthographicCamera _mOrthoCam;
		
		
		
		bool _mRotation;

		glm::vec3 _mCameraPosition = { 0.0f,0.0f,0.0f };
		float _mCameraRotation = 0.0f;
		float _mCameraTranslationSpeed = 1.0f;
		float _mCameraRotationSpeed = 180.5f;

	};
}


