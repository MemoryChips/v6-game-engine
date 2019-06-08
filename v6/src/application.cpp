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

  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  float vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                           0.0f,  0.0f,  0.5f, 0.0f};

  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  uint32_t indices[3] = {0, 1, 2};
  indexBuffer.reset(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

  std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
 			out vec3 v_Position;
 			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

  std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
 			in vec3 v_Position;
 			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

  m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
}

Application::~Application() {}

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

    m_Shader->Bind();
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT,
                   nullptr);

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
