﻿#include "gnmpch.h"
#include "WindowsInput.h"

#include "Ganymede/Application.h"

#include <GLFW/glfw3.h>

namespace Ganymede {
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keyCode) {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {xPos, yPos};
    }

    float WindowsInput::GetMouseXImpl() {
        auto[x, y] = GetMousePositionImpl();
        return x;        
    }

    float WindowsInput::GetMouseYImpl() {
        auto[x, y] = GetMousePositionImpl();
        return y;        
    }

}
