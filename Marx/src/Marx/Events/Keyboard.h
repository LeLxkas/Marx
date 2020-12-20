#pragma once

#include "Event.h"

namespace Marx
{

	class MARX_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_keyCode; }

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagKeyboard)
	protected:
		KeyEvent(int keyCode)
			: m_keyCode(keyCode)
		{}
	protected:
		int m_keyCode;
	};

	class MARX_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount)
		{}
	public:
		int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPress: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPress)
	protected:
		int m_repeatCount;
	};

	class MARX_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keyCode)
			: KeyEvent(keyCode)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyRelease: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyRelease)
	};
}