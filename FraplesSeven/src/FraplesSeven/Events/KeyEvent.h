#pragma once



#include "Events.h"


namespace Boost
{
	class FPL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode()const { return _mKeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput )
	protected:
		KeyEvent(int key) : _mKeyCode(key) {}
		int _mKeyCode;
	};

	class FPL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int keyRepeat) : KeyEvent(keycode), _mKeyRepeat(keyRepeat) { }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << _mKeyCode << "( " << _mKeyRepeat << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int _mKeyCode;
		int _mKeyRepeat;
	};

	class FPL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyRleased) : KeyEvent(keyRleased){}
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _mKeyCode;

			return ss.str();
		}
	private:
	};
}