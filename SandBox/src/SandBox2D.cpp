#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "experiments/ParticleSystem.h"
#include "experiments/Random.h"

static const uint32_t s_mapWidth = 24;
static const char* s_MapTiles = 
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDWWWWWWWWWWWW"
"WWWWWDDDDDDDDDDDWWWWWWWW"
"WWWWDDDDDDDDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWDDDWWWDDDDDDDDDDDDWWWW"
"WDDDDWWWDDDDDDDDDDDDDDDW"
"WWDDDDDDDDDDDDDDDDDDDDWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWWDDDDDDDDDDDDWWWWWW"
"WWWWWWWWWDDDDDDWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;	
								
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

	_mSpriteSheet = Fraples::Texture2D::Create("assets/Sprites/GameSpritesTest/Spritesheet/RPGpack_sheet_2X.png");

	
	m_MapWidth = s_mapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_mapWidth;
	
	_mRPGBarrel = Fraples::SubTexture2D::CreateFromCoords(_mSpriteSheet, { 0, 11 }, { 128, 128 });

	_sTextureMap['D'] = Fraples::SubTexture2D::CreateFromCoords(_mSpriteSheet, { 6, 11 }, { 128, 128 });
	_sTextureMap['W'] = Fraples::SubTexture2D::CreateFromCoords(_mSpriteSheet, {11, 11}, {128, 128});


	//_mProps.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	_mProps.ColorBegin = { Fraples::Random::Float(), Fraples::Random::Float(), Fraples::Random::Float(), 1.0f };
	_mProps.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	_mProps.SizeBegin = 0.5f, _mProps.SizeVariation = 0.3f, _mProps.SizeEnd = 0.0f;
	_mProps.LifeTime = 1.0f;
	_mProps.Velocity = { 0.0f, 0.0f };
	_mProps.VelocityVariation = { 3.0f, 1.0f };
	_mProps.Position = { 0.0f, 0.0f };

	_mCameraCtrl.SetZoomLevel(10.0f);
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
		/*
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
		*/


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

	Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * s_mapWidth];
			std::shared_ptr<Fraples::SubTexture2D> texture;
			if (_sTextureMap.find(tileType) != _sTextureMap.end())
			{
				texture = _sTextureMap[tileType];
			}
			else
			{
				texture = _mRPGBarrel;
			}
			Fraples::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, y - m_MapHeight / 2.0f,  0.5f }, { 1.0f, 1.0f }, texture);
		}
	}

	/*Fraples::Renderer2D::DrawQuad({ 0.0f, 0.0f,  0.0f }, { 1.0f, 1.0f }, _mSheep);
	Fraples::Renderer2D::DrawQuad({ 0.0f, 1.0f,  0.0f }, { 1.0f, 1.0f }, _mSuperSheep);
	Fraples::Renderer2D::DrawQuad({ 2.0f, 0.0f,  0.0f }, { 1.0f, 1.0f }, _mGreenland);*/

	Fraples::Renderer2D::EndScene();
}

void SandBox2D::OnDetach()
{
	FPL_PROFILE_FUNCTION();
}



void SandBox2D::OnImGuiRender()
{


	// ######################### DOCK SPACE #############################################

	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	bool dockspaceOpen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

			if (ImGui::MenuItem("Exit"))
				Fraples::Application().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	FPL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = Fraples::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCounts);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_mSquareColor));
	uint32_t textureId = _mCheckBoardTex->GetRendererID();
	ImGui::Image((void*)textureId, ImVec2{ 64.0f,64.0f });
	ImGui::End();

	ImGui::End();
}

void SandBox2D::OnEvent(Fraples::Event& e)
{
	_mCameraCtrl.OnEvent(e);

}
