#pragma once

#include "Core.h"

namespace Fraples
{
	class  Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
	public:
		inline static bool  IsKeyPressed(int keyCode) { return _sInstance->IsKeyPressedImpl(keyCode); }
		
		inline static bool  IsMouseButtonPressed(int button) { return _sInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return _sInstance->GetMousePosImpl(); }
		inline static float  GetMouseX() { return _sInstance->GetMouseXImpl(); }
		inline static float  GetMouseY() { return _sInstance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual std::pair<float, float> GetMousePosImpl() = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* _sInstance;

		
	};
}