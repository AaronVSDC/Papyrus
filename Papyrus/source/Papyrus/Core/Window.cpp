#include "Window.h"
#include "Papyrus/Platform/Windows/WindowsWindow.h"
#include "Papyrus/Platform/Linux/LinuxWindow.h"


//todo: don't know if this is overkill because glfw is already cross platform. But im keeping this for now just in case we need some platform specific code in the future. 
namespace Papyrus
{ 

#ifdef PPR_PLATFORM_WINDOWS

	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
#elif defined(PPR_PLATFORM_LINUX)

	Window* Window::create(const WindowProps& props)
	{
		return new LinuxWindow(props); 
	}
#endif

}