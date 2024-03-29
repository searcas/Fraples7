

#pragma once

#include "FplPCH.h"
#include "FraplesSeven/Core/Core.h"

namespace Fraples
{
	enum class EventType
	{
		NONE = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};
	enum EventCategory
	{
		NONE                     = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class Application;
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName()    const = 0;
		virtual int GetCategoryFlags()   const = 0;
		virtual std::string ToString()   const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		bool _mHandled = false;
	protected:
	};
	class EventDispatcher
	{
	
	public:
		EventDispatcher(Event& event):_mEvent(event) { }

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (_mEvent.GetEventType() == T::GetStaticType())
			{
				_mEvent._mHandled = func(static_cast<T&>(_mEvent));
				return true;
			}
			return false;
		}
	private:
		Event& _mEvent;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}