#include "FplPCH.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Fraples
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
		: _mProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _mViewMatrix(1.0f)
	{
		_mViewProjectionMatrix = _mProjectionMatrix * _mViewMatrix;

	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		_mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_mViewProjectionMatrix = _mProjectionMatrix * _mViewMatrix;

	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _mPosition) * glm::rotate(glm::mat4(1.0f),glm::radians(_mRotation), glm::vec3(0, 0, 1));

		_mViewMatrix = glm::inverse(transform);
		_mViewProjectionMatrix = _mProjectionMatrix * _mViewMatrix;
	}
}