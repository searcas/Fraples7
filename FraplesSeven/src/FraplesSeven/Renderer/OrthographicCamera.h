#pragma once

#include "glm/glm.hpp"



namespace Fraples
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return _mPosition; };
		inline void SetPosition(const glm::vec3& position) { _mPosition = position; RecalculateViewMatrix(); }
		
		inline float GetRotation() const { return _mRotation; };
		inline void SetRotation(const float& rotation) { _mRotation = rotation; RecalculateViewMatrix(); }

		inline const glm::mat4& GetProjectionMatrix() const { return _mProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return _mViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return _mViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 _mProjectionMatrix;
		glm::mat4 _mViewMatrix;
		glm::mat4 _mViewProjectionMatrix;

		glm::vec3 _mPosition = { 0.0f,0.0f,0.0f };
		float _mRotation = 0.0f;
	};
}