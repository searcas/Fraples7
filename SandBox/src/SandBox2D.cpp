#include "SandBox2D.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& fn) :_mName(name), _mFunc(fn), _mStopped(false)
	{
		_mStartTimePoint = std::chrono::high_resolution_clock::now();

	}
	~Timer()
	{
		if (!_mStopped)
			Stop();
	}
	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_mStartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		_mStopped = true;

		float duration = (float)(end - start) / 1000;
		_mFunc({ _mName, duration });
	}
private:
	const char* _mName;
	std::chrono::time_point<std::chrono::steady_clock> _mStartTimePoint;
	bool _mStopped;

	Fn _mFunc;
};
 

#define PROFILING_TOOL(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { _mProfile.push_back(profileResult); })

SandBox2D::SandBox2D() :Layer("SandBox2D"), _mCameraCtrl(1280.0f / 720.0f, true)
{
}

void SandBox2D::OnAttach()
{
	_mRandomTexture = Fraples::Texture2D::Create("assets/texture/dirt.png");

}

void SandBox2D::OnUpdate(Fraples::TimeSteps ts) 
{
	//update
	PROFILING_TOOL("SandBox2D::OnUpdate ");
	{
		PROFILING_TOOL("CameraControlOnUpdate ");
		_mCameraCtrl.OnUpdate(ts);
	}
	//Renderer
	{
		PROFILING_TOOL("Renderer Preparation ");
		Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fraples::RenderCommands::Clear();
	}
	{
		PROFILING_TOOL("Renderer Draw ");
		Fraples::Renderer2D::BeginScene(_mCameraCtrl.GetCamera());
		Fraples::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f  }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Fraples::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.4f, 0.9f, 1.0f });
		Fraples::Renderer2D::DrawQuad({ 0.3f, 0.2f },  { 0.5f, 0.75f }, _mRandomTexture);
		Fraples::Renderer2D::EndScene();
	}
}

void SandBox2D::OnDetach()
{
}



void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_mSquareColor));
	for (auto& result : _mProfile)
	{
		char lab[50];
		strcpy(lab, "%.3fms ");
		strcat(lab, result.Name);
		ImGui::Text(lab, result.Time);
	}
	_mProfile.clear();
	ImGui::End();
}

void SandBox2D::OnEvent(Fraples::Event& e)
{
	_mCameraCtrl.OnEvent(e);

}
