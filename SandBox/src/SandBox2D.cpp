#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"



SandBox2D::SandBox2D() :Layer("SandBox2D"), _mCameraCtrl(1280.0f / 720.0f, true)
{
}

void SandBox2D::OnAttach()
{




}
void SandBox2D::OnUpdate(Fraples::TimeSteps ts) 
{
	_mCameraCtrl.OnUpdate(ts);

	Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Fraples::RenderCommands::Clear();

	Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());


	Fraples::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Fraples::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.4f, 0.9f, 1.0f });
	Fraples::Renderer2D::EndScene();

}

void SandBox2D::OnDetach()
{
}



void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_mSquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Fraples::Event& e)
{
	_mCameraCtrl.OnEvent(e);

}
