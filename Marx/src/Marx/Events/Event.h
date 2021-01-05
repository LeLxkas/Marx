#pragma once

#include "Marx/Core.h"

#include <string>
#include <functional>
#include <sstream>

namespace Marx
{
	typedef int EventFlag;

	using EventCallbackFunc = std::function<void(class Event&)>;

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowFocusLoss,
		KeyPress, KeyRelease, KeyType,
		MouseMove, MouseScroll, MouseHScroll, MouseButtonPress, MouseButtonRelease,
		ControllerConnect, ControllerDisconnect,
		ControllerTriggerMove, ControllerStickMove, ControllerButtonPress, ControllerButtonRelease
	};

	enum EventFlags : EventFlag
	{
		None = 0,
		EventFlagApplication = FLAG(0),
		EventFlagDeviceConnection = FLAG(1),
		EventFlagInput = FLAG(2),
		EventFlagKeyboard = FLAG(3),
		EventFlagMouse = FLAG(4),
		EventFlagMouseButton = FLAG(5),
		EventFlagController = FLAG(6),
		EventFlagControllerAnalog = FLAG(7),
		EventFlagControllerButton = FLAG(8),
	};

	#define EVENT_CLASS_TYPE(type)   static EventType getStaticType() { return EventType::##type; }\
                                     virtual EventType getType() const override { return getStaticType(); }\
                                     virtual const char* getName() const override { return #type; }
	#define EVENT_CLASS_FLAGS(flags) virtual EventFlag getFlags() const override { return flags; }

	class Window;

	class MARX_API Event
	{
	public:
		Event() = default;
		Event(Window* pWnd)
			: m_pWnd(pWnd)
		{}
	public:
		virtual EventType getType() const = 0;
		virtual EventFlag getFlags() const = 0;
		virtual const char* getName() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool hasFlag(EventFlag flag)
		{
			return getFlags() & flag;
		}
		Window* getWnd() const { return m_pWnd; }
	public:
		bool handled = false;
	protected:
		Window* m_pWnd = nullptr;
	};

	class MARX_API EventDispatcher
	{
		template <typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{}
	public:
		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getType() == T::getStaticType())
			{
				m_event.handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}