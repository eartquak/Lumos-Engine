#pragma once
#include "Core.h"

namespace Lumos {
	class LUMOS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();
}

