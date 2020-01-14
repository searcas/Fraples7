#pragma once

#include "Fraples.h"


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
private:
	Fraples::OrthographicCameraController _mCameraCtrl;
	//temp
	std::shared_ptr<Fraples::Shader> _mFlatColorShader;
	std::shared_ptr<Fraples::VertexArray> _mSquareVA;
	std::shared_ptr<Fraples::Texture2D>_mRandomTexture;
	glm::vec4 _mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f};

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};
	std::vector<ProfileResult> _mProfile;
};
