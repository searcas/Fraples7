#pragma once
#include "FraplesSeven/Layer.h"

namespace Fraples
{

	class FPL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach()override;
		void OnDetach()override;
		void OnUpdate()override;
		void OnEvent(Event& e)override;
	private:
		float _mTime = 0.0f;
	};

}
