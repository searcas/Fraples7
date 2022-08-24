#pragma once

#include "Core.h"
#include "InputKeys.h"

namespace Fraples
{
	class  Input
	{
	public:
		static bool IsKeyPressed(unsigned int keyCode);
		static bool IsMouseButtonPressed(unsigned int button); 
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}