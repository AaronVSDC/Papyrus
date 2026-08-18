#include "Application.h"
#include "Papyrus/Log.h"
#include "Papyrus/Events/ApplicationEvent.h"

namespace Papyrus 
{
	Application::Application()
	{
		PPR_LOG_INIT;
		m_Window = std::unique_ptr<Window>(Window::create()); 
	}

	Application::~Application()
	{
	}
	void Application::run()
	{
		while (m_Running)
		{
			m_Window->update(); 
		}
	}

}