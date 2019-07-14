#include "render-command.h"

#include "platform/opengl/opengl-renderer-api.h"

namespace v6 {

RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
