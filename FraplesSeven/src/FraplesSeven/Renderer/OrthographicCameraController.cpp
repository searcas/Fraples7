#include "FplPCH.h"
#include "OrthographicCameraController.h"
#include "FraplesSeven/Core/Input.h"
#include "FraplesSeven/Core/KeyCode.h"
#include "FraplesSeven/Core/Core.h"


namespace Fraples
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		:_mAspectRatio(aspectRatio), _mBounds({ -_mAspectRatio * _mZoomLevel, _mAspectRatio * _mZoomLevel, -_mZoomLevel, _mZoomLevel }), 
		_mOrthoCam(_mBounds.left,_mBounds.right,_mBounds.bottom,_mBounds.top),
		_mRotation(rotation)
	{
	}
	
	void OrthographicCameraController::OnUpdate(TimeSteps ts)
	{
		FPL_PROFILE_FUNCTION();
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
		FPL_PROFILE_FUNCTION();
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<MouseScrollEvent>(FPL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FPL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
		
	}
	
	void OrthographicCameraController::CalculateView()
	{
		_mBounds = { -_mAspectRatio * _mZoomLevel, _mAspectRatio * _mZoomLevel, -_mZoomLevel, _mZoomLevel };
		_mOrthoCam.SetProjection(_mBounds.left, _mBounds.right, _mBounds.bottom, _mBounds.top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& ev)
	{
		FPL_PROFILE_FUNCTION();
		_mZoomLevel -= ev.GetYOffset() * 0.25f;
		_mZoomLevel = std::max(_mZoomLevel, 0.25f);
		CalculateView();
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& ev)
	{
		FPL_PROFILE_FUNCTION();
		_mAspectRatio -= (float)ev.GetWidth() / (float)ev.GetHeight();
		CalculateView();
		return false;
	}
}