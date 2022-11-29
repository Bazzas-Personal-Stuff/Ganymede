#include "gnmpch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Ganymede/Application.h"
#include "Ganymede/KeyCodes.h"
// Temporary

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ganymede {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
        
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = (time > 0.f) ? (time - m_Time) : (1.f / 60.f);
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void ImGuiLayer::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(GNM_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendPlatformName = "imgui_impl_ganymede";
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        
        ImGui_ImplOpenGL3_Init("#version 410");
        

        
    }

    void ImGuiLayer::OnDetach() {
        Layer::OnDetach();
    }

    void ImGuiLayer::UpdateKeyModifiers(int mods) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(ImGuiMod_Ctrl, (mods & GNM_MOD_CONTROL) != 0);
        io.AddKeyEvent(ImGuiMod_Shift, (mods & GNM_MOD_SHIFT) != 0);
        io.AddKeyEvent(ImGuiMod_Alt, (mods & GNM_MOD_ALT) != 0);
        io.AddKeyEvent(ImGuiMod_Super, (mods & GNM_MOD_SUPER) != 0);
    }

    
    // ImGuiKey ImGuiLayer::GLFWToImGuiKey(int key)
    ImGuiKey GNMToImGuiKey(int key)
    {
        switch (key)
        {
            case GNM_KEY_TAB: return ImGuiKey_Tab;
            case GNM_KEY_LEFT: return ImGuiKey_LeftArrow;
            case GNM_KEY_RIGHT: return ImGuiKey_RightArrow;
            case GNM_KEY_UP: return ImGuiKey_UpArrow;
            case GNM_KEY_DOWN: return ImGuiKey_DownArrow;
            case GNM_KEY_PAGE_UP: return ImGuiKey_PageUp;
            case GNM_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
            case GNM_KEY_HOME: return ImGuiKey_Home;
            case GNM_KEY_END: return ImGuiKey_End;
            case GNM_KEY_INSERT: return ImGuiKey_Insert;
            case GNM_KEY_DELETE: return ImGuiKey_Delete;
            case GNM_KEY_BACKSPACE: return ImGuiKey_Backspace;
            case GNM_KEY_SPACE: return ImGuiKey_Space;
            case GNM_KEY_ENTER: return ImGuiKey_Enter;
            case GNM_KEY_ESCAPE: return ImGuiKey_Escape;
            case GNM_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
            case GNM_KEY_COMMA: return ImGuiKey_Comma;
            case GNM_KEY_MINUS: return ImGuiKey_Minus;
            case GNM_KEY_PERIOD: return ImGuiKey_Period;
            case GNM_KEY_SLASH: return ImGuiKey_Slash;
            case GNM_KEY_SEMICOLON: return ImGuiKey_Semicolon;
            case GNM_KEY_EQUAL: return ImGuiKey_Equal;
            case GNM_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
            case GNM_KEY_BACKSLASH: return ImGuiKey_Backslash;
            case GNM_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case GNM_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
            case GNM_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
            case GNM_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
            case GNM_KEY_NUM_LOCK: return ImGuiKey_NumLock;
            case GNM_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
            case GNM_KEY_PAUSE: return ImGuiKey_Pause;
            case GNM_KEY_KP_0: return ImGuiKey_Keypad0;
            case GNM_KEY_KP_1: return ImGuiKey_Keypad1;
            case GNM_KEY_KP_2: return ImGuiKey_Keypad2;
            case GNM_KEY_KP_3: return ImGuiKey_Keypad3;
            case GNM_KEY_KP_4: return ImGuiKey_Keypad4;
            case GNM_KEY_KP_5: return ImGuiKey_Keypad5;
            case GNM_KEY_KP_6: return ImGuiKey_Keypad6;
            case GNM_KEY_KP_7: return ImGuiKey_Keypad7;
            case GNM_KEY_KP_8: return ImGuiKey_Keypad8;
            case GNM_KEY_KP_9: return ImGuiKey_Keypad9;
            case GNM_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
            case GNM_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
            case GNM_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
            case GNM_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
            case GNM_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
            case GNM_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
            case GNM_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
            case GNM_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
            case GNM_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
            case GNM_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
            case GNM_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
            case GNM_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
            case GNM_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case GNM_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
            case GNM_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
            case GNM_KEY_MENU: return ImGuiKey_Menu;
            case GNM_KEY_0: return ImGuiKey_0;
            case GNM_KEY_1: return ImGuiKey_1;
            case GNM_KEY_2: return ImGuiKey_2;
            case GNM_KEY_3: return ImGuiKey_3;
            case GNM_KEY_4: return ImGuiKey_4;
            case GNM_KEY_5: return ImGuiKey_5;
            case GNM_KEY_6: return ImGuiKey_6;
            case GNM_KEY_7: return ImGuiKey_7;
            case GNM_KEY_8: return ImGuiKey_8;
            case GNM_KEY_9: return ImGuiKey_9;
            case GNM_KEY_A: return ImGuiKey_A;
            case GNM_KEY_B: return ImGuiKey_B;
            case GNM_KEY_C: return ImGuiKey_C;
            case GNM_KEY_D: return ImGuiKey_D;
            case GNM_KEY_E: return ImGuiKey_E;
            case GNM_KEY_F: return ImGuiKey_F;
            case GNM_KEY_G: return ImGuiKey_G;
            case GNM_KEY_H: return ImGuiKey_H;
            case GNM_KEY_I: return ImGuiKey_I;
            case GNM_KEY_J: return ImGuiKey_J;
            case GNM_KEY_K: return ImGuiKey_K;
            case GNM_KEY_L: return ImGuiKey_L;
            case GNM_KEY_M: return ImGuiKey_M;
            case GNM_KEY_N: return ImGuiKey_N;
            case GNM_KEY_O: return ImGuiKey_O;
            case GNM_KEY_P: return ImGuiKey_P;
            case GNM_KEY_Q: return ImGuiKey_Q;
            case GNM_KEY_R: return ImGuiKey_R;
            case GNM_KEY_S: return ImGuiKey_S;
            case GNM_KEY_T: return ImGuiKey_T;
            case GNM_KEY_U: return ImGuiKey_U;
            case GNM_KEY_V: return ImGuiKey_V;
            case GNM_KEY_W: return ImGuiKey_W;
            case GNM_KEY_X: return ImGuiKey_X;
            case GNM_KEY_Y: return ImGuiKey_Y;
            case GNM_KEY_Z: return ImGuiKey_Z;
            case GNM_KEY_F1: return ImGuiKey_F1;
            case GNM_KEY_F2: return ImGuiKey_F2;
            case GNM_KEY_F3: return ImGuiKey_F3;
            case GNM_KEY_F4: return ImGuiKey_F4;
            case GNM_KEY_F5: return ImGuiKey_F5;
            case GNM_KEY_F6: return ImGuiKey_F6;
            case GNM_KEY_F7: return ImGuiKey_F7;
            case GNM_KEY_F8: return ImGuiKey_F8;
            case GNM_KEY_F9: return ImGuiKey_F9;
            case GNM_KEY_F10: return ImGuiKey_F10;
            case GNM_KEY_F11: return ImGuiKey_F11;
            case GNM_KEY_F12: return ImGuiKey_F12;
            default: return ImGuiKey_None;
        }
    }


    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        int mouseButton = e.GetMouseButton();
        UpdateKeyModifiers(e.GetMods());
        
        if(mouseButton >= 0 && mouseButton < ImGuiMouseButton_COUNT) {
            io.AddMouseButtonEvent(mouseButton, true);
        }

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        int mouseButton = e.GetMouseButton();
        UpdateKeyModifiers(e.GetMods());

        if(mouseButton >= 0 && mouseButton < ImGuiMouseButton_COUNT) {
            io.AddMouseButtonEvent(mouseButton, false);
        }

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(e.GetOffsetX(), e.GetOffsetY());

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        // ImGuiKey imgui_key = ImGuiLayer::GLFWToImGuiKey(e.GetKeyCode());
        ImGuiKey imgui_key = GNMToImGuiKey(e.GetKeyCode());
        io.AddKeyEvent(imgui_key, true);

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        // ImGuiKey imgui_key = ImGuiLayer::GLFWToImGuiKey(e.GetKeyCode());
        ImGuiKey imgui_key = GNMToImGuiKey(e.GetKeyCode());
        io.AddKeyEvent(imgui_key, false);

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        int keyCode = e.GetKeyCode();
        if(keyCode > 0 && keyCode < 0x10000) {
            io.AddInputCharacter((unsigned int) e.GetKeyCode());
        }

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1, 1);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
        
    }


}
