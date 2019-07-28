#pragma once

#include "Events.h"




namespace Fraples
{
	class FPL_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) :_mX(x), _mY(y) {}
		
		inline float GetX()const { return _mX; }
		inline float GetY()const { return _mY; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << _mX << ", " << _mY;
			return ss.str();
		}
		//Events Type/Category
		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
	private:
		//mouse X, Y
		float _mX;
		float _mY;
	};
	class FPL_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset) : _mXOffset(xOffset), _mYOffset(yOffset){}
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << _mXOffset<< ", " << _mYOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput );
		//Where We Scrolled
		inline float GetXOffset()const { return _mXOffset; }
		inline float GetYOffset()const { return _mYOffset; }
	private:
		float _mXOffset;
		float _mYOffset;
	

	};
	class FPL_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton()const { return _mMbutton; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		//Protected constructor to prevent creating event.
		
	protected:
		MouseButtonEvent(int msButtonKey):_mMbutton(msButtonKey) {}
		int _mMbutton;
	};
	class FPL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int ButtonKey) : MouseButtonEvent(ButtonKey) {}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << _mMbutton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed);
	};
	class FPL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{

	public:
		MouseButtonReleasedEvent(int msButton) : MouseButtonEvent(msButton) {}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << _mMbutton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

}