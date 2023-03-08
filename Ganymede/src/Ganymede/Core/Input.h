#pragma once
#include "Ganymede/Core/Core.h"
#include "glm/glm.hpp"

namespace Ganymede {
    class GANYMEDE_API Input {
    public:
        inline static bool GetKey(int keyCode) { return s_Instance->GetKeyImpl(keyCode); }
        inline static bool GetMouseButton(int button) { return s_Instance->GetMouseButtonImpl(button); }
        inline static glm::vec2 GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        
    protected:
        virtual bool GetKeyImpl(int keyCode) = 0;
        virtual bool GetMouseButtonImpl(int button) = 0;
        virtual glm::vec2 GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
    private:
        static Scope<Input> s_Instance;
    };
}