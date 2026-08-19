#include "Application.h"
#include "Papyrus/Log.h"

namespace Papyrus 
{
	Application::Application()
	{
		PPR_LOG_INIT;
		m_Window = std::unique_ptr<Window>(Window::create()); 
		m_Window->setEventCallback([this](Event& e) {onEvent(e); });
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

	void Application::onEvent(Event& e)
	{

		EventDispatcher dispatcher(e);
		bool success = dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return onWindowClose(e); });

		PPR_CORE_TRACE("{0}", e); 
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false; 
		return true;
	}

}