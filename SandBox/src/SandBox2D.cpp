#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "experiments/ParticleSystem.h"
#include "experiments/Random.h"
SandBox2D::SandBox2D()
	: Layer("SandBox2D"), _mCameraCtrl(1280.0f / 720.0f), _mSquareColor({ 0.2f,0.3f,0.8f,1.0f })
{
}

using namespace Fraples::Experiment;
void SandBox2D::OnAttach()
{
	FPL_PROFILE_FUNCTION();
	_mRandomTexture = Fraples::Texture2D::Create("assets/texture/dirt.png");
	_mCheckBoardTex = Fraples::Texture2D::Create("../Checkerboard.png");
	//_mProps.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	_mProps.ColorBegin = { Fraples::Random::Float(), Fraples::Random::Float(), Fraples::Random::Float(), 1.0f };
	_mProps.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	_mProps. SizeBegin = 0.5f, _mProps.SizeVariation = 0.3f, _mProps.SizeEnd = 0.0f;
	_mProps.LifeTime = 1.0f;
	_mProps.Velocity = { 0.0f, 0.0f };
	_mProps.VelocityVariation = { 3.0f, 1.0f };
	_mProps.Position = { 0.0f, 0.0f };

	
}

void SandBox2D::OnUpdate(Fraples::TimeSteps ts)
{
	//update
	FPL_PROFILE_FUNCTION();
	_mCameraCtrl.OnUpdate(ts);
	//Renderer
	Fraples::Renderer2D::ResetStats();
	{
		FPL_PROFILE_SCOPE("Renderer Preparation ");
		Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fraples::RenderCommands::Clear();
	}
	{
		FPL_PROFILE_SCOPE("Renderer Draw ");
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());
		Fraples::Renderer2D::RenderRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(rotation), { 0.8f, 0.2f, 0.3f, 1.0f });
		Fraples::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fraples::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, _mSquareColor);

		Fraples::Renderer2D::DrawQuad({ 0.0f, 0.0f,  -0.1f }, { 20.0f, 20.0f, }, _mCheckBoardTex, 10.0f);
		Fraples::Renderer2D::RenderRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), _mCheckBoardTex, 20.0f);
		Fraples::Renderer2D::EndScene();

		Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());
		for (float i = -5.0f; i < 5.0f; i += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (i + 5.0f) / 10.0f, 0.7f };
				Fraples::Renderer2D::DrawQuad({ x, i }, { 0.45f, 0.45f }, color);
			}
		}
		Fraples::Renderer2D::EndScene();
	}

	if (Fraples::Input::IsMouseButtonPressed(FPL_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Fraples::Input::GetMousePosition();
		auto width = Fraples::Application::GetApp().GetWindow().GetWidth();
		auto height = Fraples::Application::GetApp().GetWindow().GetHeight();

		auto bounds = _mCameraCtrl.GetBounds();
		auto pos = _mCameraCtrl.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		_mProps.Position = { x + pos.x, y + pos.y };
		for (size_t i = 0; i < 50; i++)
		{
			_mParticle.Emit(_mProps);
		}

	}
	_mParticle.OnUpdate(ts);
	_mParticle.OnRender(_mCameraCtrl.GetCamera());
}

void SandBox2D::OnDetach()
{
	FPL_PROFILE_FUNCTION();
}



void SandBox2D::OnImGuiRender()
{
	FPL_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	auto stats = Fraples::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCounts);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_mSquareColor));
	
	ImGui::End();
}

void SandBox2D::OnEvent(Fraples::Event& e)
{
	_mCameraCtrl.OnEvent(e);

}
