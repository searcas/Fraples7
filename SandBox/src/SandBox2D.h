#pragma once

#include "Fraples.h"
#include "experiments/ParticleSystem.h"

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
public:
	Fraples::OrthographicCameraController _mCameraCtrl;
	//temp
	std::shared_ptr<Fraples::Shader> _mFlatColorShader;
	std::shared_ptr<Fraples::VertexArray> _mSquareVA;
	std::shared_ptr<Fraples::Texture2D>_mRandomTexture;

	std::shared_ptr<Fraples::Texture2D>_mCheckBoardTex;
	std::shared_ptr<Fraples::Texture2D>_mSpriteSheet;
	std::shared_ptr<Fraples::Texture2D>_mGreenSprites;

	
	std::shared_ptr<Fraples::SubTexture2D>_mRPGBarrel;

	Fraples::shared<Fraples::FrameBuffer> _mFrameBuffer;

	glm::vec4 _mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};


	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, std::shared_ptr<Fraples::SubTexture2D>>_sTextureMap;
};
