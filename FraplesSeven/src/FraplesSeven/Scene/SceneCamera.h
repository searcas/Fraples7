#pragma once
#include "../Renderer/Camera.h"

namespace Fraples
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		void SetOrthograpihc(float size, float nearClip, float farClip);
		void SetViewPortSize(uint32_t width, uint32_t height);
		float GetOrthographicSize() const { return _mOrthographicSize; }
		void SetOrthographicSize(float orthographicSize) { _mOrthographicSize = orthographicSize; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		float _mOrthographicSize = 10.0f;
		float _mOrthograhpicNear = - 1.0f;
		float _mOrthograhpicFar = 1.0f; 

		float _mAspectRatio = 0.0f;
	};
}
