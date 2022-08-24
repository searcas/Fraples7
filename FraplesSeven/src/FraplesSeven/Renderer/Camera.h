#pragma once
#include "glm/glm.hpp"

namespace Fraples
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection) :_mProjection(projection)
		{ }
		virtual ~Camera() = default;
		const glm::mat4& GetProjection() const  { return _mProjection; }
	protected:
		glm::mat4 _mProjection{1.0f};
	};

}