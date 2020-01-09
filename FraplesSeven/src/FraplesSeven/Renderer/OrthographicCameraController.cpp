#include "FplPCH.h"
#include "OrthographicCameraController.h"
#include "FraplesSeven/Core/Input.h"
#include "FraplesSeven/Core/KeyCode.h"
#include "FraplesSeven/Core/Core.h"


namespace Fraples
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		:_mAspectRatio(aspectRatio), _mOrthoCam(-_mAspectRatio * _mZoomLevel, _mAspectRatio * _mZoomLevel, -_mZoomLevel, _mZoomLevel),_mRotation(rotation)
	{
	}
	
	void OrthographicCameraController::OnUpdate(TimeSteps ts)
	{
		//FPL_CLIENT_INFO("Delta Time:({0}s, {1}ms)", ts, ts.GetMilliSeconds());
		if (Input::IsKeyPressed(FPL_KEY_A))
			_mCameraPosition.x -= _mCameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(FPL_KEY_D))
			_mCameraPosition.x += _mCameraTranslationSpeed * ts;
	
		if (Input::IsKeyPressed(FPL_KEY_W))
			_mCameraPosition.y += _mCameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(FPL_KEY_S))
			_mCameraPosition.y -= _mCameraTranslationSpeed * ts;
	
		if (_mRotation)
		{
			if (Input::IsKeyPressed(FPL_KEY_R))
				_mCameraRotation += _mCameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(FPL_KEY_Q))
				_mCameraRotation -= _mCameraRotationSpeed * ts;
			_mOrthoCam.SetRotation(_mCameraRotation);
		}
		_mOrthoCam.SetPosition(_mCameraPosition);

		_mCameraTranslationSpeed = _mZoomLevel;
	}
	
	void OrthographicCameraController::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseScrollEvent>(FplBindeventFn(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FplBindeventFn(OrthographicCameraController::OnWindowResize));
		
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& ev)
	{
		_mZoomLevel -= ev.GetYOffset() * 0.25f;
		_mZoomLevel = std::max(_mZoomLevel, 0.25f);
		_mOrthoCam.SetProjection(-_mAspectRatio * _mZoomLevel, _mAspectRatio * _mZoomLevel, -_mZoomLevel, _mZoomLevel);
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& ev)
	{
		_mAspectRatio -= (float)ev.GetWidth() / (float)ev.GetHeight();
		_mOrthoCam.SetProjection(-_mAspectRatio * _mZoomLevel, _mAspectRatio * _mZoomLevel, -_mZoomLevel, _mZoomLevel);
		return false;
	}
}