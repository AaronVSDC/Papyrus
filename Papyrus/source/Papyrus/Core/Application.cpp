#include "Application.h"
#include "Papyrus/Log.h"
#include "Papyrus/Core/Time.h"
#include "Papyrus/Event/EventSystem.h"
namespace Papyrus 
{
	Application::Application()
	{
		PPR_LOG_INIT;
		m_Window = std::unique_ptr<Window>(Window::create());
		EventSystem::subscribeAll(this);
	}

	Application::~Application()
	{
	}
	void Application::run()
	{

		auto lastTime = std::chrono::high_resolution_clock::now(); 
		while (m_Running)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now(); 
			const double deltaTime = std::chrono::duration<double>(currentTime - lastTime).count(); 
			lastTime = currentTime; 

			Time::update(deltaTime); 
			m_Window->update();

		}
	}

	void Application::onEvent(Event& e)
	{
		switch (e.getType())
		{
			case PPR_SID("EVENT_WINDOW_CLOSE"):
			{
				m_Running = false;
			}
		}

		PPR_CORE_TRACE("{0}", e.toDebugString());


	}

}