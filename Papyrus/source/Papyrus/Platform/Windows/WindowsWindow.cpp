#include "WindowsWindow.h"
#include "Papyrus/Log.h"

namespace Papyrus
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props); 
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown(); 
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		m_Data.title = props.title; 
		m_Data.width = props.width; 
		m_Data.height = props.height;

		PPR_CORE_INFO("Creating WindowsWindow {0} ({1}, {2})", props.title, props.width, props.height); 

		if (!s_GLFWInitialized)
		{
			int succes = glfwInit(); 
			PPR_CORE_ASSERT(succes, "Could not initialize GLFW."); 
			s_GLFWInitialized = true; 
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), m_Data.title.c_str(), nullptr, nullptr); 
		glfwMakeContextCurrent(m_Window); 
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		setVSync(true); 
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_Window); 
	}

	void WindowsWindow::update()
	{
		glfwPollEvents(); 
		glfwSwapBuffers(m_Window); 
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0); 
		m_Data.vSync = enabled; 
	}

	bool WindowsWindow::isVSync() const
	{
		return m_Data.vSync; 
	}

}