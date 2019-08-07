#include<Fraples.h>


class ExampleLayer : public Fraples::Layer
{
public:
	ExampleLayer() : Fraples::Layer("Example")
	{
		
	}
	void OnUpdate()override
	{


	}
	void OnEvent(Fraples::Event& e)override
	{
		if (e.GetEventType() == Fraples::EventType::KeyPressed)
		{
			Fraples::KeyPressedEvent& event = (Fraples::KeyPressedEvent&)e;
			FPL_CLIENT_INFO("{0}",(char)event.GetKeyCode())

		}
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