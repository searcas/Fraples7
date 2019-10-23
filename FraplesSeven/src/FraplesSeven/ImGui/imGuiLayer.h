#pragma once
#include "FraplesSeven/Core/Layer.h"
#include "FraplesSeven/Events/MouseEvent.h"
#include "FraplesSeven/Events/KeyEvent.h"
#include "FraplesSeven/Events/AppEvent.h"
namespace Fraples
{

	class FPL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach()	override;
		virtual void OnDetach()	override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float _mTime = 0.0f;
	};

}
