#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#ifdef PPR_PLATFORM_WINDOWS

extern Papyrus::Application* Papyrus::CreateApplication(); 


int main(int argc, char** argv) 
{
	auto app = Papyrus::CreateApplication(); 
	app->run();
	delete app;
}
#endif

#endif