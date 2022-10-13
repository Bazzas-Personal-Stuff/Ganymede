#pragma once

#include "Event.h"
#include <sstream>

namespace Ganymede {

    class GANYMEDE_API KeyEvent : Event {
    public:
        inline int GetKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        
    protected:
        KeyEvent(int keycode) : m_keyCode(keycode) {}

        int m_keyCode;
    };


    class GANYMEDE_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
        
    private:
        int m_repeatCount;
    };
}
