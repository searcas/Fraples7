#include<Fraples.h>

class ExampleLayer : public Fraples::Layer
{
public:
	ExampleLayer() : Fraples::Layer("Example")
	{

	}
	void OnUpdate()override
	{
		FPL_CLIENT_INFO("ExampleLayer::Update");
	}
	void OnEvent(Fraples::Event& e)override
	{
		FPL_CLIENT_TRACE("{0}", e);
	}

private:

};




class SandBox : public Fraples::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}
	~SandBox()
	{

	}
};

Fraples::Application* Fraples::CreateApplication()
{
	return new SandBox();
}