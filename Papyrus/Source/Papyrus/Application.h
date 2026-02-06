#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace Papyrus
{
	
	class PAPYRUS_API Application
	{

	public: 

		Application(); 
		virtual ~Application();  

		void run(); 
	};

	//To be defined in client
	Application* createApplication();

}

#endif