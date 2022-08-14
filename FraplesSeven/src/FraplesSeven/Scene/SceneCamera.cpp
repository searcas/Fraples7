#include "FplPCH.h"
#include "SceneCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Fraples
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthograpihc(float size, float nearClip, float farClip)
	{
		_mProjectionType = ProjectionType::Orthographic;
		_mOrthographicSize = size;
		_mOrthograhpicNear = nearClip;
		_mOrthograhpicFar = farClip;

		RecalculateProjection();

	}
	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		_mProjectionType = ProjectionType::Perspective;
		_mPerspectiveFOV = verticalFOV;
		_mPerspectiveNear = nearClip;
		_mPerspectiveFar= farClip;

		RecalculateProjection();

	}
	void SceneCamera::SetViewPortSize(uint32_t width, uint32_t height)
	{
		_mAspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}
	void SceneCamera::RecalculateProjection() 
	{
		if (_mProjectionType == ProjectionType::Perspective)
		{
			_mProjection = glm::perspective(_mPerspectiveFOV, _mAspectRatio, _mPerspectiveNear, _mPerspectiveFar);
		}
		else
		{
			float orthoLeft = -_mOrthographicSize * _mAspectRatio * 0.5;
			float orthoRight = _mOrthographicSize * _mAspectRatio * 0.5;

			float orthoBottom = -_mOrthographicSize * 0.5;
			float orthoTop = _mOrthographicSize * 0.5;

			_mProjection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, _mOrthograhpicNear, _mOrthograhpicFar);
		}
		
	}
}