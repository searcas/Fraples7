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

	glm::vec4 _mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};

	Fraples::Experiment::ParticleSystem _mParticle;
	Fraples::Experiment::ParticleProps _mProps;
};
