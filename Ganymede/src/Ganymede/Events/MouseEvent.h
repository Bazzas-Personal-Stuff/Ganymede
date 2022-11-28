#pragma once
#include "Event.h"

namespace Ganymede {

class GANYMEDE_API MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

    inline float GetX() const { return m_mouseX; }
    inline float GetY() const { return m_mouseY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    
private:
    float m_mouseX;
    float m_mouseY;
};


class GANYMEDE_API MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x, float y) : m_offsetX(x), m_offsetY(y) {}

    inline float GetOffsetX() const { return m_offsetX; }
    inline float GetOffsetY() const { return m_offsetY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_offsetX;
    float m_offsetY;
};


class GANYMEDE_API MouseButtonEvent : public Event {
public:
    inline int GetMouseButton() const { return m_button; }
    inline int GetMods() const { return m_mods; }
    EVENT_CLASS_CATEGORY(EventCategoryMouseButton)
    
protected:
    MouseButtonEvent(int button, int mods) : m_button(button), m_mods(mods) {}
    int m_button;
    int m_mods;
};


class GANYMEDE_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button, int mods) : MouseButtonEvent(button, mods) {}
    
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_button << ", Mods: " << m_mods;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};


class GANYMEDE_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button, int mods) : MouseButtonEvent(button, mods) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_button << ", Mods: " << m_mods;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};
}
