#pragma once

#ifdef LUMOS_PLATFORM_WINDOWS

extern Lumos::Application* Lumos::CreateApplication();

int main(int argc, char ** argv)
{
	auto app = Lumos::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif // LUMOS_PLATFORM_WINDOWS
