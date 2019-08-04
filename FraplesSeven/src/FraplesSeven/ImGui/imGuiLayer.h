#pragma once
#include "FraplesSeven/Layer.h"
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

		void OnAttach()override;
		void OnDetach()override;
		void OnUpdate()override;
		void OnEvent(Event& e)override;
	private:
		bool OnMouseButtonPressEvent(MouseButtonPressedEvent& eve);
		bool OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& eve);
		bool OnMouseMoveEvent(MouseMovedEvent& eve);
		bool OnMouseScrollEvent(MouseScrollEvent& eve);
		bool OnKeyReleasedEvent(KeyReleasedEvent& eve);
		bool OnKeyPressedEvent(KeyPressedEvent& eve);
		bool OnKeyTypedEvent(KeyTypedEvent& eve);
		bool OnWindowResizeEvent(WindowResizeEvent& eve);

	private:
		float _mTime = 0.0f;
	};

}
