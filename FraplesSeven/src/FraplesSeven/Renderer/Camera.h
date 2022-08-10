#pragma once
#include "glm/glm.hpp"

namespace Fraples
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection) :_mProjection(projection)
		{ }
		~Camera() = default;
		const glm::mat4& GetProjection() { return _mProjection; }
	private:
		glm::mat4 _mProjection;
	};

}