#include "gnmpch.h"
#include "Time.h"

#include "GLFW/glfw3.h"

namespace Ganymede {
    Time Time::s_Time = Time();
    void Time::UpdateDelta() {
        float time = (float)glfwGetTime();
        s_Time.m_AppDelta = time - s_Time.m_LastFrameTime;
        s_Time.m_LastFrameTime = time;
    }
}
