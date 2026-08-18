#ifndef PAPYRUS_WINDOW_H
#define PAPYRUS_WINDOW_H
#include "Papyrus/Core/Core.h"
#include "Papyrus/Events/Event.h"

namespace Papyrus
{

    struct WindowProps
    {
        std::string title; 
        unsigned int width; 
        unsigned int height;

        WindowProps(const std::string& _title = "Papyrus Engine", unsigned int _width = 1280, unsigned int _height = 720)
            :title(_title), width(_width), height(_height) {}
    };

    class PAPYRUS_API Window
    {
    public:
        Window() = default; 
        Window(Window&) = delete; 
        Window(Window&&) = delete; 
        Window& operator=(Window&) = delete; 
        Window& operator=(Window&&) = delete; 

        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void update() = 0; 

        virtual unsigned int getWidth() const = 0; 
        virtual unsigned int getHeight() const = 0; 

        virtual void setEventCallback(const EventCallbackFn& callback) = 0; 
        virtual void setVSync(bool enabled) = 0; 
        virtual bool isVSync() const = 0; 

        static Window* create(const WindowProps& props = WindowProps()); 

    };
}

#endif