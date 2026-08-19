#ifndef PAPYRUS_ENTRY_POINT_H
#define PAPYRUS_ENTRY_POINT_H

//todo: think if it could be useful to have different main functions for linux and windows (wwinmain) .

extern Papyrus::Application* Papyrus::createApplication(); 

 
int main(int, char**) 
{
	auto app = Papyrus::createApplication();
	app->run();
	delete app;
}

#endif