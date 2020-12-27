#pragma once

#include "Event.h"

namespace Marx
{
	class MARX_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(Window* pWnd, float x, float y)
			: Event(pWnd), m_x(x), m_y(y)
		{}
	public:
		inline float getX() const { return m_x; }
		inline float getY() const { return m_y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMove: " << m_x << ", " << m_y;
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagMouse)
			EVENT_CLASS_TYPE(MouseMove)
	private:
		float m_x;
		float m_y;
	};

	class MARX_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(Window* pWnd, float delta)
			: Event(pWnd), m_delta(delta)
		{}
	public:
		inline float getDelta() const { return m_delta; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScroll: " << m_delta;
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagMouse)
			EVENT_CLASS_TYPE(MouseScroll)
	private:
		float m_delta;
	};

	class MARX_API MouseHScrollEvent : public Event
	{
	public:
		MouseHScrollEvent(Window* pWnd, float delta)
			: Event(pWnd), m_delta(delta)
		{}
	public:
		inline float getDelta() const { return m_delta; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseHScroll: " << m_delta;
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagMouse)
			EVENT_CLASS_TYPE(MouseHScroll)
	private:
		float m_delta;
	};

	class MARX_API MouseButtonEvent : public Event
	{
	public:
		inline int getButton() const { return m_button; }

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagMouse | EventFlagMouseButton)
	protected:
		MouseButtonEvent(Window* pWnd, int button)
			: Event(pWnd), m_button(button)
		{}
	protected:
		int m_button;
	};

	class MARX_API MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(Window* pWnd, int button)
			: MouseButtonEvent(pWnd, button)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPress: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPress)
	};

	class MARX_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(Window* pWnd, int button)
			: MouseButtonEvent(pWnd, button)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonRelease: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonRelease)
	};
}