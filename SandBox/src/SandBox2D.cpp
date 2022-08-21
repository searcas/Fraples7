#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "FraplesSeven/Core/Log.h"
#include "FraplesSeven/Scene/SceneSerializer.h"
#include "FraplesSeven/Utils/PlatformUtils.h"
		
SandBox2D::SandBox2D()
	: Layer("SandBox2D"), _mCameraCtrl(1280.0f / 720.0f), _mSquareColor({ 0.2f,0.3f,0.8f,1.0f })
{
}  

void SandBox2D::OnAttach()
{
	FPL_PROFILE_FUNCTION();
	_mCheckBoardTex = Fraples::Texture2D::Create("../Checkerboard.png");
	Fraples::FrameBufferSpec spec;
	spec.width = 1280;
	spec.height = 720;
	_mFrameBuffer = Fraples::FrameBuffer::Create(spec);

	_mActiveScene = std::make_shared<Fraples::Scene>();
#if 0
	auto& squareA = _mActiveScene->CreateEntity("SquareA");
	squareA.AddComponent<Fraples::SpriteRendererComponent>(glm::vec4(1.0f, 0.5f, 0.5f, 0.5f));
	auto& squareB = _mActiveScene->CreateEntity("SquareB");
	squareB.AddComponent<Fraples::SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 1.0f, 0.5f));
	
	_mSquareEntity = squareA;

	_mCameraEntity = _mActiveScene->CreateEntity("Camera A");
	_mCameraEntity.AddComponent<CameraComponent>();

	_mSecondCameraEntity = _mActiveScene->CreateEntity("Camera B");
	auto& cc = _mSecondCameraEntity.AddComponent<CameraComponent>();
	cc.mainCamera = false;


	class CameraController : public ScriptableEntity
	{
	public:
		void OnCreate()
		{
			auto& translation = GetComponent<TransformComponent>().Translation;
			translation.x += rand() % 5;
			FPL_CORE_INFO("Initial Call OnCreate");
		}
		void OnDestroy()
		{
			FPL_CORE_INFO("Destroyed");
		}
		void OnUpdate(TimeSteps ts)
		{
			auto& translation = GetComponent<TransformComponent>().Translation;
			float speed = 5.0f;
			if (Input::IsKeyPressed('A'))
			{
				translation.x -= speed * ts;
			}
			else if (Input::IsKeyPressed('D'))
			{
				translation.x += speed * ts;

			}
			if (Input::IsKeyPressed('W'))
			{
				translation.y -= speed * ts;
			}
			else if (Input::IsKeyPressed('S'))
			{
				translation.y += speed * ts;

			}
		}
	private:
	};
	_mSecondCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
	_mCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
	_mSceneHierarchyPanel.SetScene(_mActiveScene);


}

void SandBox2D::OnUpdate(Fraples::TimeSteps ts)
{
	//update
	FPL_PROFILE_FUNCTION();
	FrameBufferSpec spec = _mFrameBuffer->GetFrameBufferSpec();
	
	if ( _mViewPortSize.x > 0.0f && _mViewPortSize.y > 0.0f && spec.width != _mViewPortSize.x || spec.height != _mViewPortSize.y)
	{
		_mFrameBuffer->Resize((uint32_t)_mViewPortSize.x, (uint32_t)_mViewPortSize.y );
		_mCameraCtrl.OnResize(_mViewPortSize.x, _mViewPortSize.y);
		_mActiveScene->OnViewPortResize(_mViewPortSize.x, _mViewPortSize.y);
	}
	if(_mViewportFocused)
		_mCameraCtrl.OnUpdate(ts);
	//Renderer
	Fraples::Renderer2D::ResetStats();
	{
		_mFrameBuffer->Bind();
		Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fraples::RenderCommands::Clear();
		_mActiveScene->OnUpdate(ts);
		_mFrameBuffer->Unbind();
		
	}
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
	ImGuiStyle& style = ImGui::GetStyle();
	float minWindSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	style.WindowMinSize.x = minWindSizeX;
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
			if (ImGui::MenuItem("New","CTRL + N"))
			{
				NewScene();
			}
			if (ImGui::MenuItem("Open", "CTRL + O"))
			{
				
				OpenScene();

			}
			if (ImGui::MenuItem("Save", "CTRL + S"))
			{
				
				SaveScene();
			}
			if (ImGui::MenuItem("Save as", "CTRL + SHIFT + S"))
			{
				SaveSceneAs();
			}
			if (ImGui::MenuItem("Exit"))
				Fraples::Application().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	FPL_PROFILE_FUNCTION();
	_mSceneHierarchyPanel.OnImGuiRender();
	ImGui::Begin("Stats");
	auto stats = Fraples::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCounts);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
	ImGui::Begin("Viewport");
	_mViewportFocused = ImGui::IsWindowFocused();
	_mViewportHovered = ImGui::IsWindowHovered();
	Fraples::Application::GetApp().GetImGuiLayer()->SetBlockEvents(!_mViewportFocused || !_mViewportHovered);

	ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
	_mViewPortSize = { viewPortSize.x, viewPortSize.y };
	uint32_t textureId = _mFrameBuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureId, ImVec2{ _mViewPortSize.x, _mViewPortSize.y });
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::End();

	ImGui::End();
}

void SandBox2D::OnEvent(Fraples::Event& e)
{
	_mCameraCtrl.OnEvent(e);
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressedEvent>(FPL_BIND_EVENT_FN(SandBox2D::OnKeyPressed));
}

void SandBox2D::SaveSceneAs()
{
	const std::string& path = FileDialogs::SaveFile("Fraples7 Scene (*.fpl)\0*.fpl;*.txt");
	if (!path.empty())
	{
		SceneSerializer serializer(_mActiveScene);
		serializer.Serialize(path);
	}
}

void SandBox2D::SaveScene()
{
	if (_mSceneSaved.empty())
	{
		const std::string& path = FileDialogs::SaveFile("Fraples7 Scene (*.fpl)\0*.fpl;*.txt");
		if (!path.empty())
		{
			SceneSerializer serializer(_mActiveScene);
			serializer.Serialize(path);
			_mSceneSaved = path;
		}
	}
	else
	{
		SceneSerializer serializer(_mActiveScene);
		serializer.Serialize(_mSceneSaved);
	}
}

void SandBox2D::OpenScene()
{
	const std::string& path = FileDialogs::SaveFile("Fraples7 Scene (*.fpl)\0*.fpl");
	if (!path.empty())
	{
		_mActiveScene = std::make_shared<Fraples::Scene>();
		_mActiveScene->OnViewPortResize((uint32_t)_mViewPortSize.x, (uint32_t)_mViewPortSize.y);
		_mSceneHierarchyPanel.SetScene(_mActiveScene);
		SceneSerializer serializer(_mActiveScene);
		serializer.Deserialize(path);
		_mSceneSaved = path;
	}
}

void SandBox2D::NewScene()
{
	_mActiveScene = std::make_shared<Fraples::Scene>();
	_mActiveScene->OnViewPortResize((uint32_t)_mViewPortSize.x, (uint32_t)_mViewPortSize.y);
	_mSceneHierarchyPanel.SetScene(_mActiveScene);
}

bool SandBox2D::OnKeyPressed(KeyPressedEvent& e)
{
	if (e.GetKeyRepeat() > 0)
	{
		return false;
	}
	bool control = Input::IsKeyPressed(KEY_LEFT_CONTROL) || Input::IsKeyPressed(KEY_RIGHT_CONTROL);
	bool shift = Input::IsKeyPressed(KEY_LEFT_SHIFT) || Input::IsKeyPressed(KEY_RIGHT_SHIFT);

	switch (e.GetKeyCode())
	{
	case KEY_S:
		if (control && shift)
		{
			SaveSceneAs();
		}
		if (control && !shift)
		{
			SaveScene();
		}
		break;
	case KEY_N:
		if (control)
		{
			NewScene();
		}
		break;
	case KEY_O:
		if (control)
		{
			OpenScene();
		}
		break;
	}
	return false;
}
