#ifndef PAPYRUSENGINE_WINDOWS_WINDOW_H
#define PAPYRUSENGINE_WINDOWS_WINDOW_H

#include "Papyrus/Core/Window.h"

namespace Papyrus
{
	class WindowsWindow final : public Window
	{
	public: 
		WindowsWindow(const WindowProps& props); 
		~WindowsWindow() override;

		void update() override; 

		[[nodiscard]] unsigned int width() const override { return m_Width; }
		[[nodiscard]] unsigned int height() const override { return m_Height; }

		//void setVSync(bool enabled) override;
		//bool isVSync() const override;

		[[nodiscard]] HWND handle() const {return m_WindowHandle;}
	private: 
		void init();
		void shutdown();

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private: 

		HWND m_WindowHandle = nullptr;

		std::string m_Title;
		unsigned int m_Width, m_Height;
		//bool m_VSync;

	};
}



#endif