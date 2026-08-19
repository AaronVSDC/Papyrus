#include "WindowsWindow.h"
#include "Papyrus/Log.h"
#include "Papyrus/Events/ApplicationEvent.h"
#include "Papyrus/Events/MouseEvent.h"
#include "Papyrus/Events/KeyEvent.h"

namespace Papyrus
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		PPR_CORE_ERROR("GLFW Error ({0}): {1}", error, description); 
	}

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

		PPR_CORE_INFO("Creating Windows Window: {0} ({1}, {2})", props.title, props.width, props.height); 

		if (!s_GLFWInitialized)
		{
			int succes = glfwInit(); 
			PPR_CORE_ASSERT(succes, "Could not initialize GLFW."); 
			glfwSetErrorCallback(GLFWErrorCallback); 
			s_GLFWInitialized = true; 
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), m_Data.title.c_str(), nullptr, nullptr); 
		glfwMakeContextCurrent(m_Window); 
		glfwSetWindowUserPointer(m_Window, &m_Data); 
		setVSync(true); 

		//set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.width = width;
				data.height = height;

				WindowResizeEvent windowResizeEvent(width, height); 
				data.eventCallback(windowResizeEvent);

			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window)); 
				WindowCloseEvent windowCloseEvent; 
				data.eventCallback(windowCloseEvent); 
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent keyPressedEvent(key);
						data.eventCallback(keyPressedEvent); 
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent keyReleasedEvent(key); 
						data.eventCallback(keyReleasedEvent); 
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent keyPressedEvent(key, true); 
						data.eventCallback(keyPressedEvent); 
						break;
					}
				}

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent mouseButtonPressedEvent(button);
						data.eventCallback(mouseButtonPressedEvent);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent mouseButtonReleasedEvent(button);
						data.eventCallback(mouseButtonReleasedEvent);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent mouseScrolledEvent(static_cast<float>(xOffset), static_cast<float>(yOffset)); 
				data.eventCallback(mouseScrolledEvent); 
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				
				MouseMovedEvent mouseMovedEvent(static_cast<float>(xPos), static_cast<float>(yPos));
				data.eventCallback(mouseMovedEvent); 
			});
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