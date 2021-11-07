#pragma once
#include "FplPCH.h"
#include "FraplesSeven/Core/Core.h"
#include "FraplesSeven/Events/Events.h"


namespace Fraples
{
	struct WindowProperties
	{
		std::string _mTitle;
		unsigned int _mWidth;
		unsigned int _mHeight;

		WindowProperties(const std::string& title = "FrapleSeven Engine", 
			unsigned int width = 1280, unsigned int height = 720) 
			: _mTitle(title), _mWidth(width), _mHeight(height) { }
	};
	class Window
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth()  const = 0;
		virtual unsigned int GetHeight() const = 0;

		//WindowAttributes

		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		//If you not specifing properties it use default ones 
		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}