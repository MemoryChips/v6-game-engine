#include "sandbox.h"
#include "memory"
#include "platform/opengl/opengl-shader.h"
#include "v6.h"
#include <gtc/type_ptr.hpp>

using namespace v6;

ExampleLayer::ExampleLayer()
    : Layer("Example"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f),
      cameraRotation(0.0f), cameraSpeed(1.0f), cameraRotationSpeed(10.1f),
      squarePosition(0.0f) {
  pVertexArray.reset(VertexArray::Create());

  float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                           0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

  Ref<VertexBuffer> pVertexBuffer;
  pVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::Float4, "a_Color"}};
  pVertexBuffer->SetLayout(layout);
  pVertexArray->AddVertexBuffer(pVertexBuffer);

  uint32_t indices[3] = {0, 1, 2};
  Ref<IndexBuffer> pIndexBuffer;
  pIndexBuffer.reset(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  pVertexArray->SetIndexBuffer(pIndexBuffer);

  pSquareVA.reset(VertexArray::Create());

  // clang-format off
  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  
    0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
  };

  Ref<VertexBuffer> pSquareVB;
  pSquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  pSquareVB->SetLayout({
    {ShaderDataType::Float3, "a_Position"},
    {ShaderDataType::Float2, "a_TexCoord"}
  });
  pSquareVA->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> pSquareIB;
  pSquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                         sizeof(uint32_t)));
  pSquareVA->SetIndexBuffer(pSquareIB);

  std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

 			out vec3 v_Position;
 			out vec4 v_Color;

 			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

  pShader.reset(v6::Shader::Create(vertexSrc, fragmentSrc));
  std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

 			out vec3 v_Position;
 			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

  std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
 			in vec3 v_Position;
      uniform vec4 uColor;
 			void main()
			{
				color = uColor;
			}
		)";

  pFlatColorShader.reset(
      v6::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

  pTextureShader.reset(
      Shader::Create("./sandbox/assets/shaders/texture.glsl"));
  
  pTexture = Texture2D::create("./sandbox/assets/textures/checkerboard.png");
  pChernoLogoTexture = Texture2D::create("./sandbox/assets/textures/ChernoLogo.png");
  
  std::dynamic_pointer_cast<OpenGLShader>(pTextureShader)->bind();
  std::dynamic_pointer_cast<OpenGLShader>(pTextureShader)
            ->UploadUniformInt("u_Texture", 0);
  // pTexture.reset();
}

void ExampleLayer::onUpdate(double tsSec) {
  // LOG_TRACE("Time step is: {0}", ts);
  if (Input::isKeyPressed(V6_KEY_LEFT)) {
    cameraPosition.x += cameraSpeed * tsSec;
  } else if (Input::isKeyPressed(V6_KEY_RIGHT)) {
    cameraPosition.x -= cameraSpeed * tsSec;
  }
  if (Input::isKeyPressed(V6_KEY_UP)) {
    cameraPosition.y -= cameraSpeed * tsSec;
  } else if (Input::isKeyPressed(V6_KEY_DOWN)) {
    cameraPosition.y += cameraSpeed * tsSec;
  }
  if (Input::isKeyPressed(V6_KEY_A)) {
    cameraRotation -= cameraRotationSpeed * tsSec;
  } else if (Input::isKeyPressed(V6_KEY_D)) {
    cameraRotation += cameraRotationSpeed * tsSec;
  }

  if (Input::isKeyPressed(V6_KEY_J)) {
    squarePosition.x -= cameraSpeed * tsSec;
  } else if (Input::isKeyPressed(V6_KEY_L)) {
    squarePosition.x += cameraSpeed * tsSec;
  }
  if (Input::isKeyPressed(V6_KEY_I)) {
    squarePosition.y -= cameraSpeed * tsSec;
  } else if (Input::isKeyPressed(V6_KEY_K)) {
    squarePosition.y += cameraSpeed * tsSec;
  }

  v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  v6::RenderCommand::Clear();

  camera.SetPosition(cameraPosition);
  camera.SetRotation(cameraRotation);

  v6::Renderer::BeginScene(camera);

  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

  // glm::vec4 blueColor(0.2, 0.3, 0.8, 1.0);
  glm::vec4 blueColor(squareColor.x, squareColor.y, squareColor.z, 1.0);
  glm::vec4 redColor(0.8, 0.2, 0.3, 1.0);

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 20; x++) {
      glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
      v6::Renderer::Submit(pFlatColorShader, pSquareVA, transform);
      if (x % 2 == 0)
        std::dynamic_pointer_cast<OpenGLShader>(pFlatColorShader)
            ->UploadUniformFloat4("uColor", redColor);
      else
        std::dynamic_pointer_cast<OpenGLShader>(pFlatColorShader)
            ->UploadUniformFloat4("uColor", blueColor);
    }
  }
  glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
  pTexture->bind();
  v6::Renderer::Submit(pTextureShader, pSquareVA, scale2);
  pChernoLogoTexture->bind();
  v6::Renderer::Submit(pTextureShader, pSquareVA, scale2);

  // triangle
  // v6::Renderer::Submit(pShader, pVertexArray);

  v6::Renderer::EndScene();
}

void ExampleLayer::onImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
  ImGui::End();
}

void ExampleLayer::onEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<KeyPressedEvent>(
      V6_BIND_EVENT_FN(ExampleLayer::onKeyPressedEvent));
}
bool ExampleLayer::onKeyPressedEvent([[maybe_unused]] KeyPressedEvent &e) {
  // auto keyCode = e.GetKeyCode();
  // LOG_TRACE("key code pressed: {0}", keyCode);

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