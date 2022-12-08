#pragma once
#include "Timestep.h"

namespace Ganymede {
    class Time {
    public:
        static Timestep Delta() { return s_Time.m_AppDelta; }
        static void UpdateDelta();
        static void SetDelta(Timestep delta) { s_Time.m_AppDelta = delta; }
    private:
        static Time s_Time;
        Timestep m_AppDelta = 0.0f;
        float m_LastFrameTime = 0.0f;
    };
    
}
