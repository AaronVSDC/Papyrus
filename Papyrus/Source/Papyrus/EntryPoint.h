#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#ifdef PPR_PLATFORM_WINDOWS

extern Papyrus::Application* Papyrus::createApplication(); 

 
int main(int, char**) 
{
	Papyrus::Log::init(); 
	PPR_CORE_WARN("Core logger warning"); 
	PPR_INFO("Client logger info");  
	PPR_CRITICAL("FATAL ERROR");  
	PPR_TRACE("tracing something"); 
	int var = 3; 
	PPR_CORE_TRACE("var={0}", var); 

	auto app = Papyrus::createApplication(); 
	app->run();
	delete app;
}
#endif 

#endif