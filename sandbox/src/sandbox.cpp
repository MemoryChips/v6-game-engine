#include "sandbox.h"

using namespace v6;

ExampleLayer::ExampleLayer()
    : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f),
      cameraRotation(0.0f), cameraSpeed(0.1f), cameraRotationSpeed(0.1f) {
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
      uniform mat4 u_ViewProjection;

 			out vec3 v_Position;
 			out vec4 v_Color;

 			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

      uniform mat4 u_ViewProjection;

 			out vec3 v_Position;
 			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

void ExampleLayer::onUpdate() {
  if (Input::isKeyPressed(V6_KEY_LEFT)) {
    cameraPosition.x -= cameraSpeed;
  } else if (Input::isKeyPressed(V6_KEY_RIGHT)) {
    cameraPosition.x += cameraSpeed;
  }
  if (Input::isKeyPressed(V6_KEY_UP)) {
    cameraPosition.y -= cameraSpeed;
  } else if (Input::isKeyPressed(V6_KEY_DOWN)) {
    cameraPosition.y += cameraSpeed;
  }
  if (Input::isKeyPressed(V6_KEY_A)) {
    cameraRotation -= cameraRotationSpeed;
  }
  if (Input::isKeyPressed(V6_KEY_D)) {
    cameraRotation += cameraRotationSpeed;
  }
  v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  v6::RenderCommand::Clear();

  camera.SetPosition(cameraPosition);
  camera.SetRotation(cameraRotation);

  v6::Renderer::BeginScene(camera);

  v6::Renderer::Submit(pBlueShader, pSquareVA);
  v6::Renderer::Submit(pShader, pVertexArray);

  v6::Renderer::EndScene();
}

void ExampleLayer::onImGuiRender() {}

void ExampleLayer::onEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(
      V6_BIND_EVENT_FN(ExampleLayer::onKeyPressedEvent));
}
bool ExampleLayer::onKeyPressedEvent(KeyPressedEvent &e) {
  auto keyCode = e.GetKeyCode();
  LOG_TRACE("key code pressed: {0}", keyCode);

  // if (e.GetKeyCode() == V6_KEY_LEFT) {
  //   cameraPosition.x -= cameraSpeed;
  // }
  // if (e.GetKeyCode() == V6_KEY_RIGHT) {
  //   cameraPosition.x += cameraSpeed;
  // }
  // if (e.GetKeyCode() == V6_KEY_UP) {
  //   cameraPosition.y -= cameraSpeed;
  // }
  // if (e.GetKeyCode() == V6_KEY_DOWN) {
  //   cameraPosition.y += cameraSpeed;
  // }
  return false;
}

Sandbox::Sandbox(/* args */) { pushLayer(new ExampleLayer()); }
Sandbox::~Sandbox() {}