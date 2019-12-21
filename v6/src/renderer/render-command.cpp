#include "render-command.h"
#include "core.h"
#include "platform/opengl/opengl-renderer-api.h"

namespace v6 {

Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
