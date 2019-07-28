#include<Fraples.h>

class SandBox : public Fraples::Application
{
public:
	SandBox()
	{

	}
	~SandBox()
	{

	}
};

Fraples::Application* Fraples::CreateApplication()
{
	return new SandBox();
}