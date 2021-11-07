#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

SandBox2D::SandBox2D() 
	: Layer("SandBox2D"), _mCameraCtrl(1280.0f / 720.0f, true)
{
}

void SandBox2D::OnAttach()
{
	FPL_PROFILE_FUNCTION();
	_mRandomTexture = Fraples::Texture2D::Create("assets/texture/dirt.png");
	_mCheckBoardTex = Fraples::Texture2D::Create("../Checkerboard.png");

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
	 	Fraples::Renderer2D::RenderRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f  },(rotation), { 0.8f, 0.2f, 0.3f, 1.0f });
		Fraples::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.00f, }, _mCheckBoardTex, 10.0f);
		Fraples::Renderer2D::DrawQuad({ -0.5f, -0.5f,  0.0f }, { 1.0f, 1.0f, }, _mCheckBoardTex, 20.0f);
		Fraples::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f  }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fraples::Renderer2D::RenderRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, _mCheckBoardTex, 20.0f);
		Fraples::Renderer2D::EndScene();

		Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());
		for (float i =-5.0f; i < 5.0f; i+=0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x+=0.5f)
			{
				glm::vec4 color = { ( x + 5.0f ) / 10.0f, 0.4f, (i + 5.0f) / 10.0f, 0.5f };
				Fraples::Renderer2D::DrawQuad({ x, i }, { 0.45f,0.45f }, color);
			}
		}
		Fraples::Renderer2D::EndScene();
	}
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
