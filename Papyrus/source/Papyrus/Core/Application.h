#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Papyrus/Event/Event.h"
#include "Papyrus/Event/EventListener.h"

namespace Papyrus
{
	
	class PAPYRUS_API Application : public EventListener
	{

	public: 

		Application(); 
		virtual ~Application();  

		void run(); 

		void onEvent(Event& e) override;
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true; 
	};

	//To be defined in client
	Application* createApplication();

}

#endif