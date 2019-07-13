#include "glad/glad.h"
// glad first
#include "GLFW/glfw3.h"

#include "application.h"
#include "input.h"
#include "log.h"

namespace v6 {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application *Application::sInstance = nullptr;

Application::Application(/* args */) {
  V6_ASSERT(!sInstance, "Application already exists!")
  sInstance = this;
  // Application::sInstance = this;
  pWindow = std::unique_ptr<Window>(Window::Create());
  pWindow->SetEventCallback(BIND_EVENT_FN(onEvent));

  imGuiLayer = new ImGuiLayer();
  pushOverlay(imGuiLayer);

  pVertexArray.reset(VertexArray::Create());

  float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                           0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

  std::shared_ptr<VertexBuffer> pVertexBuffer;
  pVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::Float4, "a_Color"}};
  pVertexBuffer->SetLayout(layout);
  pVertexArray->AddVertexBuffer(pVertexBuffer);

  uint32_t indices[3] = {0, 1, 2};
  std::shared_ptr<IndexBuffer> pIndexBuffer;
  pIndexBuffer.reset(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  pVertexArray->SetIndexBuffer(pIndexBuffer);

  pSquareVA.reset(VertexArray::Create());

  float squareVertices[3 * 4] = {-0.75f, -0.75f, 0.0f, 0.75f,  -0.75f, 0.0f,
                                 0.75f,  0.75f,  0.0f, -0.75f, 0.75f,  0.0f};

  std::shared_ptr<VertexBuffer> pSquareVB;
  pSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  pSquareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
  pSquareVA->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  std::shared_ptr<IndexBuffer> pSquareIB;
  pSquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                         sizeof(uint32_t)));
  pSquareVA->SetIndexBuffer(pSquareIB);

  std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
 			out vec3 v_Position;
 			out vec4 v_Color;
 			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

  std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
 			in vec3 v_Position;
 			in vec4 v_Color;
 			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = v_Color;
			}
		)";

  pShader.reset(new Shader(vertexSrc, fragmentSrc));
  std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
 			out vec3 v_Position;
 			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

  std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
 			in vec3 v_Position;
 			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

  pBlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}

void Application::pushLayer(Layer *layer) {
  layerStack.pushLayer(layer);
  layer->onAttach();
}
void Application::pushOverlay(Layer *layer) {
  layerStack.pushOverlay(layer);
  layer->onAttach();
}

void Application::onEvent(Event &e) {
  EventDispatcher d(e);
  d.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClosed));
  // LOG_CORE_TRACE("{0}", e);
  for (auto it = layerStack.end(); it != layerStack.begin();) {
    (*--it)->onEvent(e);
    if (e.Handled)
      break;
  }
}

void Application::run() {
  while (running) {
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    pBlueShader->Bind();
    pSquareVA->Bind();
    glDrawElements(GL_TRIANGLES, pSquareVA->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);
    pShader->Bind();
    pVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, pVertexArray->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);

    for (Layer *layer : layerStack)
      layer->onUpdate();

    imGuiLayer->begin();
    for (Layer *layer : layerStack)
      layer->onImGuiRender();
    imGuiLayer->end();

    pWindow->OnUpdate();
  }
}

bool Application::onWindowClosed([[maybe_unused]] WindowCloseEvent &e) {
  running = false;
  return true;
}

} // namespace v6
