#ifndef PAPYRUSENGINE_ENTRY_POINT_H
#define PAPYRUSENGINE_ENTRY_POINT_H


extern Papyrus::Application* Papyrus::createApplication(); 

#ifdef PPR_PLATFORM_WINDOWS

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HANDLE mutex = CreateMutexW(nullptr, FALSE, L"PapyrusEngine_SingleInstanceMutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBoxW(nullptr, L"Application is already running.", L"Papyrus Engine", MB_ICONWARNING);
		return 0;
	}

#ifdef PPR_DEBUG
	AllocConsole();
#endif

	auto app = Papyrus::createApplication();
	app->run();
	delete app;
	return 0;
}


#elif defined(PPR_PLATFORM_LINUX)
int main(int, char**) 
{
	auto app = Papyrus::createApplication();
	app->run();
	delete app;
}
#endif
#endif