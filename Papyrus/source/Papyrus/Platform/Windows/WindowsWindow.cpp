#include "WindowsWindow.h"
#include "Papyrus/Log.h"
#include "Papyrus/Event/Event.h"
#include "Papyrus/Event/EventSystem.h"

#include <Windowsx.h>

namespace Papyrus
{

	static const wchar_t* WINDOWS_CLASS_NAME = L"PapyrusWindowClass";
	static bool s_ClassRegistered = false;

	WindowsWindow::WindowsWindow(const WindowProps& props)
		:m_Title(props.title),m_Width(props.width),m_Height(props.height)
	{
		init();
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown(); 
	}

	void WindowsWindow::init()
	{
		PPR_CORE_INFO("Creating Windows Window: {0} ({1}, {2})", m_Title, m_Width, m_Height);

		HINSTANCE hInstance = GetModuleHandle(nullptr);

		if (!s_ClassRegistered)
		{
			WNDCLASSW wc = {};
			wc.lpfnWndProc = WindowProc;
			wc.hInstance = hInstance;
			wc.lpszClassName  = WINDOWS_CLASS_NAME;
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

			PPR_CORE_ASSERT(RegisterClassW(&wc), "Could not register Win32 window class.");
			s_ClassRegistered = true;
		}

		std::wstring wideTitle(m_Title.begin(), m_Title.end());

		m_WindowHandle = CreateWindowExW(
			0,
			WINDOWS_CLASS_NAME,
			wideTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			static_cast<int>(m_Width), static_cast<int>(m_Height),
			nullptr, nullptr, hInstance, nullptr);

		PPR_CORE_ASSERT(m_WindowHandle, "Could not create Win32 window.");

		SetWindowLongPtrW(m_WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);

	}

	void WindowsWindow::shutdown()
	{
		DestroyWindow(m_WindowHandle);
	}

	void WindowsWindow::update()
	{
		MSG msg;
		while (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//--------------------------------------
	//USER INPUT AND WINDOW EVENTS
	//--------------------------------------
	LRESULT WindowsWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* self = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		switch (msg)
		{
			case WM_CLOSE:
			{
				Event e = PPR_MAKE_EVENT("EVENT_WINDOW_CLOSE");
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_SIZE:
			{
				unsigned int width = LOWORD(lParam);
				unsigned int height = HIWORD(lParam);
				if (self) {self->m_Width = width; self->m_Height = height;}

				Event e = PPR_MAKE_EVENT("EVENT_WINDOW_RESIZE");
				PPR_SET_EVENT_ARG_INT(e, "Width", static_cast<uint32_t>(width));
				PPR_SET_EVENT_ARG_INT(e, "Height", static_cast<uint32_t>(height));
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_KEYDOWN:
			{
				//todo: implement scancode
				bool isRepeat = (lParam & (1 << 30)) != 0;

				Event e = PPR_MAKE_EVENT("EVENT_KEY_PRESSED");
				PPR_SET_EVENT_ARG_INT(e, "KeyCode", static_cast<uint32_t>(wParam));
				PPR_SET_EVENT_ARG_INT(e, "IsRepeat", isRepeat);
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_KEYUP:
			{
				Event e = PPR_MAKE_EVENT("EVENT_KEY_RELEASED");
				PPR_SET_EVENT_ARG_INT(e, "KeyCode", static_cast<uint32_t>(wParam));
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:
			{
				uint32_t button = (msg == WM_LBUTTONDOWN) ? 0 : (msg == WM_RBUTTONDOWN) ? 1 : 2;
				Event e = PPR_MAKE_EVENT("EVENT_MOUSE_BUTTON_PRESSED");
				PPR_SET_EVENT_ARG_INT(e, "Button", button);
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
			{
				uint32_t button = (msg == WM_LBUTTONUP) ? 0 : (msg == WM_MBUTTONUP) ? 1 : 2;
				Event e = PPR_MAKE_EVENT("EVENT_MOUSE_BUTTON_RELEASED");
				PPR_SET_EVENT_ARG_INT(e, "Button", button);
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				Event e = PPR_MAKE_EVENT("EVENT_MOUSE_MOVED");
				PPR_SET_EVENT_ARG_INT(e, "X", static_cast<uint32_t>(GET_X_LPARAM(lParam)));
				PPR_SET_EVENT_ARG_INT(e, "Y", static_cast<uint32_t>(GET_Y_LPARAM(lParam)));
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA;
				Event e = PPR_MAKE_EVENT("EVENT_MOUSEWHEEL_SCROLLED");
				PPR_SET_EVENT_ARG_FLOAT(e, "YOffset", delta);
				EventSystem::broadcast(e);
				return 0;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

}
