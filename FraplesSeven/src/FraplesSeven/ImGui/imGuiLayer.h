#pragma once
#include "FraplesSeven/Core/Layer.h"
#include "FraplesSeven/Events/MouseEvent.h"
#include "FraplesSeven/Events/KeyEvent.h"
#include "FraplesSeven/Events/AppEvent.h"
namespace Fraples
{

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach()	override;
		virtual void OnDetach()	override;
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();
		void SetBlockEvents(bool set) { _mBlockEvents = set; }
		void SetDarkThemeColors();
	private:
		float _mTime = 0.0f;
		bool _mBlockEvents = true;
	};

}
