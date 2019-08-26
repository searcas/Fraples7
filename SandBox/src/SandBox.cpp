#include<Fraples.h>
#include "FraplesSeven/Core.h"
class ExampleLayer : public Fraples::Layer
{
public:
	ExampleLayer() : Fraples::Layer("Example"), _mCamera(-1.6f, 1.6f, -0.9f, 0.9f), _mCameraPosition(0.0f)
	{
		_mVertexArray.reset(Fraples::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.3f, 5.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.6f, 0.6f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.3f, 0.6f, 1.0f
		};
		std::shared_ptr<Fraples::VertexBuffer>vertexBuffer;
		vertexBuffer.reset(Fraples::VertexBuffer::Create(vertices, sizeof(vertices)));

		Fraples::BufferLayout layout = { {Fraples::ShaderDataType::Float3,"_aPosition"}, {Fraples::ShaderDataType::Float4,"_aColor"} };

		vertexBuffer->SetLayout(layout);
		_mVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Fraples::IndexBuffer>indexBuffer;
		indexBuffer.reset(Fraples::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_mVertexArray->SetIndexBuffer(indexBuffer);


		_mSquareVArray.reset(Fraples::VertexArray::Create());

		float squareVertices[3 * 4] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,	 0.75f, 0.0f,
			-0.75f,	 0.75f, 0.0f
		};

		std::shared_ptr<Fraples::VertexBuffer>squareVBuffer;
		squareVBuffer.reset(Fraples::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVBuffer->SetLayout({ {Fraples::ShaderDataType::Float3, "_aPosition"} });
		_mSquareVArray->AddVertexBuffer(squareVBuffer);


		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Fraples::IndexBuffer>squareIBuffer;
		squareIBuffer.reset(Fraples::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_mSquareVArray->SetIndexBuffer(squareIBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;
			layout(location = 1) in vec4  _aColor;
			
			out vec3 _vPosition;
			out vec4 _vColor;
			
			uniform mat4 _uViewProjectionMatrix;			

			void main()
			{
				_vPosition = _aPosition;
				_vColor = _aColor;
				gl_Position = _uViewProjectionMatrix * vec4(_aPosition, 1.0);
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
		_mShader.reset(new Fraples::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;
		
			uniform mat4 _uViewProjectionMatrix;			
	
			out vec3 _vPosition;

			void main()
			{
				_vPosition = _aPosition;
				gl_Position = _uViewProjectionMatrix * vec4(_aPosition, 1.0);
			}

			)";
		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 _vPosition;
			
			void main()
			{	
				
				 color = vec4(0.2,0.3,0.7,1.0);
			}
	)";
		_mShader2.reset(new Fraples::Shader(vertexSrc2, fragmentSrc2));
	}
	void OnUpdate() override
	{
		if (Fraples::Input::IsKeyPressed(FPL_KEY_RIGHT))
			_mCameraPosition.x += _mCameraMoveSpeed;
		else if (Fraples::Input::IsKeyPressed(FPL_KEY_LEFT))
			_mCameraPosition.x -= _mCameraMoveSpeed;
		if (Fraples::Input::IsKeyPressed(FPL_KEY_UP))
			_mCameraPosition.y += _mCameraMoveSpeed;
		else if (Fraples::Input::IsKeyPressed(FPL_KEY_DOWN))
			_mCameraPosition.y -= _mCameraMoveSpeed;
		if (Fraples::Input::IsKeyPressed(FPL_KEY_R))
			_mCameraRotation += _mCameraRotationSpeed;
		else if (Fraples::Input::IsKeyPressed(FPL_KEY_Q))
			_mCameraRotation -= _mCameraRotationSpeed;

		Fraples::RenderCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Fraples::RenderCommands::Clear();

		_mCamera.SetPosition(_mCameraPosition);
		_mCamera.SetRotation(_mCameraRotation);

		Fraples::Renderer::BeginScene(_mCamera);
		Fraples::Renderer::Submit(_mShader2, _mSquareVArray);
		Fraples::Renderer::Submit(_mShader, _mVertexArray);
		Fraples::Renderer::EndScene();


	}
	void OnEvent(Fraples::Event& e)override
	{
	}

private:
	Fraples::OrthographicCamera _mCamera;
	std::shared_ptr<Fraples::Shader> _mShader;
	std::shared_ptr<Fraples::VertexArray>_mVertexArray;

	std::shared_ptr<Fraples::VertexArray>_mSquareVArray;
	std::shared_ptr<Fraples::Shader> _mShader2;
	glm::vec3 _mCameraPosition;

	float _mCameraMoveSpeed = 0.1f;
	float _mCameraRotationSpeed = 1.5f;
	float _mCameraRotation = 0.0f;
};




class SandBox : public Fraples::Application
{
public:
	SandBox() : Fraples::Application()
	{
		
		PushLayer(new ExampleLayer());
	}
	~SandBox()
	{

	}
};

Fraples::Application* Fraples::CreateApplication()
{
	return new SandBox();
}