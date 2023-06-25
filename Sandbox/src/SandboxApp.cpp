#include <Lumos.h>

class Sandbox : public Lumos::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lumos::Application* Lumos::CreateApplication()
{
	return new Sandbox;
}