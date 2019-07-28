#pragma once
#include "Events.h"



namespace Fraples
{
	class FPL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : _mWidth(width), _mHeight(height) { }

		inline unsigned int GetHeight()const { return _mHeight; }
		inline unsigned int GetWidth()const { return _mWidth; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << _mWidth << ", " << _mHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	private:
		unsigned int _mWidth;
		unsigned int _mHeight;
	};

	class FPL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class FPL_API AppTicketEvent : public Event
	{
	public:
		AppTicketEvent() {}
		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class FPL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class FPL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

}