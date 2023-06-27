#include <Lumos.h>

class Sandbox : public Lumos::Application
{
public:
	Sandbox()
	{
		LOG_INFO("Application Created");
	}

	~Sandbox()
	{

	}
};

Lumos::Application* Lumos::CreateApplication()
{
	return new Sandbox;
}