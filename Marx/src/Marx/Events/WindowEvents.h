#pragma once

#include "Event.h"

namespace Marx
{

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(Window* pWnd)
			: Event(pWnd)
		{}

		EVENT_CLASS_FLAGS(EventFlagApplication)
			EVENT_CLASS_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(Window* pWnd, unsigned int width, unsigned int height)
			: Event(pWnd), m_width(width), m_height(height)
		{}
	public:
		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << getWidth() << ", " << getHeight();
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagApplication)
			EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(Window* pWnd)
			: Event(pWnd)
		{}

		EVENT_CLASS_FLAGS(EventFlagApplication)
			EVENT_CLASS_TYPE(WindowFocus)
	};

	class WindowFocusLossEvent : public Event
	{
	public:
		WindowFocusLossEvent(Window* pWnd)
			: Event(pWnd)
		{}

		EVENT_CLASS_FLAGS(EventFlagApplication)
			EVENT_CLASS_TYPE(WindowFocusLoss)
	};
}