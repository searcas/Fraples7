#include "FplPCH.h"


#include "imGuiLayer.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "FraplesSeven/App.h"
//TEMP
#include "GLFW/glfw3.h"
#include "glad/glad.h"	


namespace Fraples
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{

	}
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//TEMPORARY HACK SOLUTION!!
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
	}
	void ImGuiLayer::OnUpdate()
	{
		

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApp();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(),app.GetWindow().GetHeight());

		float  time = (float)glfwGetTime();
		io.DeltaTime = _mTime > 0.0 ? (time - _mTime) : (1.0f / 60.0f);
		_mTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
	}
	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(FplBindeventFn(ImGuiLayer::OnMouseButtonPressEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(FplBindeventFn(ImGuiLayer::OnMouseButtonReleaseEvent));
		dispatcher.Dispatch<MouseMovedEvent>(FplBindeventFn(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrollEvent>(FplBindeventFn(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(FplBindeventFn(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(FplBindeventFn(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(FplBindeventFn(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(FplBindeventFn(ImGuiLayer::OnWindowResizeEvent));

	}
	bool ImGuiLayer::OnMouseButtonPressEvent(MouseButtonPressedEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[eve.GetMouseButton()] = true;
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& eve)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[eve.GetMouseButton()] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMoveEvent(MouseMovedEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(eve.GetX(),eve.GetY());
		return false;
	}
	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += eve.GetXOffset();
		io.MouseWheel += eve.GetYOffset();

		return false;
	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[eve.GetKeyCode()] = true;
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& eve)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[eve.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(eve.GetWidth(), eve.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0.0f, 0.0f, eve.GetWidth(), eve.GetHeight());
		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& eve)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = eve.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		return false;
	}
	

}