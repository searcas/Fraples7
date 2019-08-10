#pragma once
#include "FraplesSeven/Window.h"
#include "FraplesSeven/Renderer/Context/GraphicsContext.h"
#include <GLFW/glfw3.h>


namespace Fraples
{
	class WindowsWindow : public Window{
public:
	WindowsWindow(const WindowProperties& prop);
	virtual ~WindowsWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return _mData._mWidth; }
	inline unsigned int GetHeight() const override { return _mData._mHeight; }

	//Window Attributes
	inline void SetEventCallBack(const EventCallBackFn& callback) override { _mData._mEventCallbackFn = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

	inline virtual void* GetNativeWindow() const { return _mWindow; }
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void ShutDown();
	private:
		GLFWwindow* _mWindow;
		GraphicsContext* _mContext;
		struct WindowData
		{
			std::string _mTitle;
			unsigned int  _mWidth, _mHeight;
			bool _mVSync;
			
			EventCallBackFn _mEventCallbackFn;
		};
		WindowData _mData;
	};
}
