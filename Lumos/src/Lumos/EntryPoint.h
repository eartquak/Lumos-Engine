#pragma once
#include "Log.h"

#ifdef LUMOS_PLATFORM_WINDOWS

extern Lumos::Application* Lumos::CreateApplication();

int main(int argc, char ** argv)
{
	Lumos::Log::Init();
	LOG_CORE_WARN("Welcome to Lumos!");

	auto app = Lumos::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // LUMOS_PLATFORM_WINDOWS
