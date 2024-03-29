#include <Fraples.h>
#include "FraplesSeven/Core/Core.h"
#include "imGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "SandBox2D.h"
//------------Entry Point---------------//
#include "FraplesSeven/Core/EntryPoint.h"
//----------------END-------------------//

class ExampleLayer : public Fraples::Layer
{
public:
	ExampleLayer() : Fraples::Layer("Example"), _mCameraCtrl(1280.0f / 720.0f, true)
	{
		_mVertexArray = Fraples::VertexArray::Create();

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.3f, 5.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.6f, 0.6f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.3f, 0.6f, 1.0f
		};
		std::shared_ptr<Fraples::VertexBuffer>vertexBuffer = Fraples::VertexBuffer::Create(vertices, sizeof(vertices));;
		

		Fraples::BufferLayout layout = { {Fraples::ShaderDataType::Float3,"_aPosition"}, {Fraples::ShaderDataType::Float4,"_aColor"} };

		vertexBuffer->SetLayout(layout);
		_mVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Fraples::IndexBuffer>indexBuffer = Fraples::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));;
		
		_mVertexArray->SetIndexBuffer(indexBuffer);


		_mSquareVArray = Fraples::VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,	0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,	0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Fraples::VertexBuffer>squareVBuffer = Fraples::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		
		squareVBuffer->SetLayout({ 
			{Fraples::ShaderDataType::Float3, "_aPosition"},
			{Fraples::ShaderDataType::Float2, "_aTexCoord"} 
			});
		_mSquareVArray->AddVertexBuffer(squareVBuffer);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fraples::IndexBuffer>squareIBuffer = Fraples::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		
		_mSquareVArray->SetIndexBuffer(squareIBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;
			layout(location = 1) in vec4  _aColor;
			
			out vec3 _vPosition;
			out vec4 _vColor;
			
			uniform mat4 _uViewProjectionMatrix;			
			uniform mat4 _uTransform;			

			void main()
			{
				_vPosition = _aPosition;
				_vColor = _aColor;
				gl_Position = _uViewProjectionMatrix * _uTransform * vec4(_aPosition, 1.0);
			}

			)";
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 _vPosition;
			in vec4 _vColor;

				
			

			void main()
			{	
				
				 color = vec4(_vPosition * 0.5 + 0.5, 1.0);
				 color=_vColor;
			}
	)";
		_mShader = Fraples::Shader::Create("VertexColorTriangle",vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;

		
			uniform mat4 _uViewProjectionMatrix;			
			uniform mat4 _uTransform;	

			out vec3 _vPosition;		
			

			void main()
			{
				_vPosition = _aPosition;
				gl_Position = _uViewProjectionMatrix * _uTransform * vec4(_aPosition, 1.0);
			}

			)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 _vPosition;
			
			uniform vec3 _uColor;

			void main()
			{	
				 color = vec4(_uColor, 1.0);
			}
	)";
		_mShader2 = Fraples::Shader::Create("FlatColor",flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = _mShaderLibrary.Load("assets/Shaders/Texture.glsl");

		_mTexture = Fraples::Texture2D::Create("assets/texture/dirt.png");

		textureShader->Bind();
		textureShader->SetUniformInt("u_Texture", 0);
	}
	void OnUpdate(Fraples::TimeSteps ts) override
	{
		_mCameraCtrl.OnUpdate(ts);

		Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fraples::RenderCommands::Clear();

		Fraples::Renderer::BeginScene(_mCameraCtrl.GetCamera());
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Fraples::Renderer::Submit(_mShader2, _mSquareVArray, transform);
			}
		}
		auto textureShader = _mShaderLibrary.GetShader("Texture");
		_mTexture->Bind();
		Fraples::Renderer::Submit(textureShader, _mSquareVArray, glm::scale(glm::mat4(1.0f),glm::vec3(1.5f)));

		//Triangle
		//Fraples::Renderer::Submit(_mShader, _mVertexArray);
		Fraples::Renderer::EndScene();


	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(_mSquareColor));
		ImGui::End();
	}
	void OnEvent(Fraples::Event& e)override
	{
		_mCameraCtrl.OnEvent(e);
	}

private:
	Fraples::ShaderLibrary _mShaderLibrary;
	std::shared_ptr<Fraples::Shader> _mShader;
	std::shared_ptr<Fraples::VertexArray>_mVertexArray;

	std::shared_ptr<Fraples::Texture2D>_mTexture;

	std::shared_ptr<Fraples::VertexArray>_mSquareVArray;
	std::shared_ptr<Fraples::Shader> _mShader2;


	Fraples::OrthographicCameraController _mCameraCtrl;
	glm::vec3 _mSquareColor = { 0.2f, 0.3f, 0.8f };

};


class SandBox : public Fraples::Application
{
public:
	SandBox() : Fraples::Application()
	{
		//PushLayer(new ExampleLayer());
		  PushLayer(new SandBox2D());
	}
	~SandBox()
	{

	}
};

Fraples::Application* CreateApplication()
{
	return new SandBox();
}