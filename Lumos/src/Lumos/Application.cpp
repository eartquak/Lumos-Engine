#include "Application.h"
#include<iostream>
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Lumos{
	Application::Application()
	{

	}
	Application::~Application()
	{
	
	}
	void Application::Run()
	{
		WindowResizeEvent e(1980, 1080);
		if (e.IsInCategory(EventCategoryApplication)) {
			LOG_INFO("This is a Resize Window Event");
			LOG_TRACE(e);
		}

		while (1);
	}
}