#pragma once

#include "gnmpch.h"
#include "Ganymede/Core/Core.h"
#include "Ganymede/Events/Event.h"

namespace Ganymede {
    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Ganymede Engine",
            unsigned int width = 1280,
            unsigned int height = 720) : Title(title), Width(width), Height(height) {
        }
    };


    class GANYMEDE_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    }; 

}