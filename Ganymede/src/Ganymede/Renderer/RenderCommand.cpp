#include "gnmpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ganymede {
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
