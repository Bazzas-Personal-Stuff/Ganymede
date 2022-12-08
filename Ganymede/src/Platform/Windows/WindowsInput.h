#pragma once
#include "Ganymede/Input.h"

namespace Ganymede {
    class WindowsInput : public Input {
    protected:
        virtual bool GetKeyImpl(int keyCode) override;
        virtual bool GetMouseButtonImpl(int button) override;
        virtual glm::vec2 GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}
