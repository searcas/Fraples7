#include "FplPCH.h"
#include "App.h"


#include "glad/glad.h"

#include "Input.h"
namespace Fraples{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::_sInstance = nullptr;

	

	Application::Application()
	{

		FPL_CORE_ASSERTS(!_sInstance, "Application already Exists");
		_sInstance = this;

		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		_mImguiLayer = new ImGuiLayer();
		PushOverLay(_mImguiLayer);

		_mVertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.3f, 5.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.6f, 0.6f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.3f, 0.6f, 1.0f
		};
		std::shared_ptr<VertexBuffer>vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = { {ShaderDataType::Float3,"_aPosition"}, {ShaderDataType::Float4,"_aColor"} };

		vertexBuffer->SetLayout(layout);
		_mVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer>indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_mVertexArray->SetIndexBuffer(indexBuffer);


		_mSquareVArray.reset(VertexArray::Create());

		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,	0.5f, 0.0f,
			-0.5f,	0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer>squareVBuffer;  
		squareVBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVBuffer->SetLayout({ {ShaderDataType::Float3, "_aPosition"} });
		_mSquareVArray->AddVertexBuffer(squareVBuffer);

		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer>squareIBuffer; 
		squareIBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_mSquareVArray->SetIndexBuffer(squareIBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;
			layout(location = 1) in vec4  _aColor;
			
			out vec3 _vPosition;
			out vec4 _vColor;

			void main()
			{
				_vPosition = _aPosition;
				_vColor = _aColor;
				gl_Position = vec4(_aPosition, 1.0);
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
		_mShader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 _aPosition;
			
			out vec3 _vPosition;

			void main()
			{
				_vPosition = _aPosition;
				gl_Position = vec4(_aPosition, 1.0);
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
		_mShader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClosed));

		for (auto it = _mLayerStack.end(); it != _mLayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e._mHandled)
				break;
		}
	}
	bool Application::OnWindowsClosed(WindowCloseEvent& winEvent)
	{
		_mRunning = false;
		return true;
	}
	void Application::Run()
	{
		while (_mRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			_mShader2->Bind();
			_mSquareVArray->Bind();
			glDrawElements(GL_TRIANGLES, _mSquareVArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			_mShader->Bind();
			_mVertexArray->Bind();
			glDrawElements(GL_TRIANGLES,_mVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _mLayerStack)
				layer->OnUpdate();
			//auto[x, y] = Input::GetMousePosition();
			//FPL_CLIENT_TRACE("{0},{1}", x, y);
			_mImguiLayer->Begin();
			for (Layer* layer : _mLayerStack)
				layer->OnImGuiRender();
			_mImguiLayer->End();

			_mWindow->OnUpdate();
		}

	}
	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer)
	{
		_mLayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverLay(Layer* overlay)
	{
		_mLayerStack.PushOverLay(overlay);
		overlay->OnAttach();
	}
}