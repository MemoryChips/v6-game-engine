#include "sandbox.h"
#include "memory"
#include "sandbox-2d.h"

#include <gtc/type_ptr.hpp>

using namespace v6;

ExampleLayer::ExampleLayer()
    : Layer("Example"), orthoCamController(1280.0f / 720.0f) {
  pVertexArray = VertexArray::Create();

  float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
                           0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
                           0.0f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

  Ref<VertexBuffer> pVertexBuffer =
      VertexBuffer::Create(vertices, sizeof(vertices));
  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::Float4, "a_Color"}};
  pVertexBuffer->SetLayout(layout);
  pVertexArray->AddVertexBuffer(pVertexBuffer);

  uint32_t indices[3] = {0, 1, 2};
  Ref<IndexBuffer> pIndexBuffer =
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
  pVertexArray->SetIndexBuffer(pIndexBuffer);

  pSquareVA = VertexArray::Create();

  // clang-format off
  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  
    0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
  };

  Ref<VertexBuffer> pSquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
  pSquareVB->SetLayout({
    {ShaderDataType::Float3, "a_Position"},
    {ShaderDataType::Float2, "a_TexCoord"}
  });
  pSquareVA->AddVertexBuffer(pSquareVB);

  uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
  Ref<IndexBuffer> pSquareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                         sizeof(uint32_t));
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
  pShader = Shader::Create("VertexPosColor",vertexSrc, fragmentSrc);

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

  pFlatColorShader = 
      Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

  auto pTextureShader = shaderLibrary.load("./sandbox/assets/shaders/texture.glsl");
  
  pTexture = Texture2D::create("./sandbox/assets/textures/checkerboard.png");
  pChernoLogoTexture = Texture2D::create("./sandbox/assets/textures/ChernoLogo.png");
  pShowerPeterArnoTexture = Texture2D::create("./sandbox/assets/textures/shower-peter-arno.png");
  
  pTextureShader->bind();
  pTextureShader->setInt("u_Texture", 0);
}

void ExampleLayer::onUpdate(Timestep ts) {
  // Update
  orthoCamController.onUpdate(ts);

  // Render
  v6::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
  v6::RenderCommand::Clear();

  v6::Renderer::BeginScene(orthoCamController.GetCamera());

  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 20; x++) {
      glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
      v6::Renderer::Submit(pFlatColorShader, pSquareVA, transform);
    }
  }
  auto pTextureShader = shaderLibrary.get("texture");
  
  glm::mat4 scale2 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
  pTexture->bind();
  Renderer::Submit(pTextureShader, pSquareVA, scale2);
  pChernoLogoTexture->bind();
  Renderer::Submit(pTextureShader, pSquareVA, scale2);

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
  orthoCamController.onEvent(e);
}

bool ExampleLayer::onKeyPressedEvent([[maybe_unused]] KeyPressedEvent &e) {
  return false;
}

Sandbox::Sandbox(/* args */) { 
  // pushLayer(new ExampleLayer()); 
  pushLayer(new Sandbox2D()); 
  }
Sandbox::~Sandbox() {}