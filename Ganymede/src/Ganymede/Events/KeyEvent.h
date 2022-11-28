#pragma once

#include "Event.h"

namespace Ganymede {

    class GANYMEDE_API KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_keyCode; }
        inline int GetMods() const { return m_mods; }
        
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        
    protected:
        KeyEvent(int keycode, int mods) : m_keyCode(keycode), m_mods(mods) {}

        int m_keyCode;
        int m_mods;
    };


    class GANYMEDE_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int mods, int repeatCount) : KeyEvent(keyCode, mods), m_repeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << ", Mods: " << m_mods << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
        
    private:
        int m_repeatCount;
    };


    class GANYMEDE_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keyCode, int mods) : KeyEvent(keyCode, mods) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode << ", Mods: " << m_mods;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class GANYMEDE_API KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keyCode, int mods) : KeyEvent(keyCode, mods) {}


        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode << ", Mods: " << m_mods;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}
