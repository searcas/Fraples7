#include "FplPCH.h"
#include "App.h"


#include "glad/glad.h"

#include "Input.h"
namespace Fraples{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::_sInstance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Fraples::ShaderDataType::Float:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float2:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float3:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Float4:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Fraples::ShaderDataType::Int:
			return GL_INT;
		case Fraples::ShaderDataType::Int2:
			return GL_INT;
		case Fraples::ShaderDataType::Int3:
			return GL_INT;
		case Fraples::ShaderDataType::Int4:
			return GL_INT;
		case Fraples::ShaderDataType::Boolean:
			return GL_BOOL;
		default:
			break;
		}
		FPL_CORE_ASSERTS(false, "Unkonwn Shader Type.");

		return 0;
	}

	Application::Application()
	{

		FPL_CORE_ASSERTS(!_sInstance, "Application already Exists");
		_sInstance = this;
		
		_mWindow = std::unique_ptr<Window>(Window::Create());
		_mWindow->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		_mImguiLayer = new ImGuiLayer();
		PushOverLay(_mImguiLayer);

		glGenVertexArrays(1, &_mVertexArray);
		glBindVertexArray(_mVertexArray);


		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.3f, 5.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.6f, 0.6f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.3f, 0.6f, 1.0f

		};

		{
		_mVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = { {ShaderDataType::Float3,"_aPosition"}, {ShaderDataType::Float4,"_aColor"}};
		_mVertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = _mVertexBuffer->GetLayout();
		for (const auto& elements : layout)
		{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, elements.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(elements.SDataType), elements.Normalized ? GL_TRUE : GL_FALSE, _mVertexBuffer->GetLayout().GetStride() , (const void*)elements.Offset);
		index++;
		}


		
		uint32_t indices[3] = { 0, 1, 2 };

		_mIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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
		_mShader.reset(new Shader(vertexSrc,fragmentSrc));
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

			_mShader->Bind();
			glBindVertexArray(_mVertexArray);
			glDrawElements(GL_TRIANGLES, _mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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