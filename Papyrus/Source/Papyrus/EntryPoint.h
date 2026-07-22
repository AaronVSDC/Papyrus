#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#ifdef PPR_PLATFORM_WINDOWS

extern Papyrus::Application* Papyrus::createApplication(); 

 
int main(int, char**) 
{
	Papyrus::Log::init(); 
	auto app = Papyrus::createApplication();
	app->run();
	delete app;
}
#endif 

#endif