﻿#include "gnmpch.h"
#include "WindowsInput.h"

#include "Ganymede/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Ganymede {
    Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

    bool WindowsInput::GetKeyImpl(int keyCode) {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::GetMouseButtonImpl(int button) {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
        
    }

    glm::vec2 WindowsInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {(float)xPos, (float)yPos};
    }

    float WindowsInput::GetMouseXImpl() {
        return GetMousePositionImpl().x;
    }

    float WindowsInput::GetMouseYImpl() {
        return GetMousePositionImpl().y;
    }

}
