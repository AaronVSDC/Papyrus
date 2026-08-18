#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"
namespace Papyrus
{
	
	class PAPYRUS_API Application
	{

	public: 

		Application(); 
		virtual ~Application();  

		void run(); 
	private:
		std::unique_ptr<Window> m_Window; 
		bool m_Running = true; 
	};

	//To be defined in client
	Application* createApplication();

}

#endif