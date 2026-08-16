#include "Application.h"
#include "Papyrus/Log.h"
#include "Papyrus/Events/ApplicationEvent.h"

namespace Papyrus 
{
	Application::Application()
	{
		PPR_LOG_INIT;
	}

	Application::~Application()
	{
	}
	void Application::run()
	{

		WindowResizeEvent e(20, 20); 
		PPR_TRACE(e);
	}

}