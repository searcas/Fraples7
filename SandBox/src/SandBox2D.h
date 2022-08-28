#pragma once

#include "Fraples.h"
#include "../Panels/SceneHierarchyPanel.h"

using namespace Fraples;

class SandBox2D : public Fraples::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Fraples::TimeSteps ts) override;
	void OnImGuiRender() override;
	void OnEvent(Fraples::Event& e) override;
	void SaveSceneAs();
	void SaveScene();
	void OpenScene();
	void NewScene();
private:
	bool OnKeyPressed(KeyPressedEvent& e);
private:
	Entity _mSquareEntity;
	Entity _mCameraEntity;
	Entity _mSecondCameraEntity;
	Fraples::shared<Fraples::Scene> _mActiveScene;
	Fraples::OrthographicCameraController _mCameraCtrl;
	//temp
	std::shared_ptr<Fraples::Shader> _mFlatColorShader;
	std::shared_ptr<Fraples::VertexArray> _mSquareVA;

	std::shared_ptr<Fraples::Texture2D>_mCheckBoardTex;
	
	std::shared_ptr<Fraples::SubTexture2D>_mRPGBarrel;

	Fraples::shared<Fraples::FrameBuffer> _mFrameBuffer;

	glm::vec4 _mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};
	glm::vec2 _mViewPortSize = {0, 0};
	glm::vec2 _mViewPortBounds[2];
	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, std::shared_ptr<Fraples::SubTexture2D>>_sTextureMap;
	bool _mViewportFocused = false;
	bool _mViewportHovered = false;
	bool _mPrimaryCamera = true;

	std::string _mSceneSaved = "";

	EngineCamera _mEngineCamera;
	SceneHierarchyPanel _mSceneHierarchyPanel;
	int _mGuizmoType = -1;
	Entity _mHoveredEntity;
};
