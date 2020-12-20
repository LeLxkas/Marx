#pragma once

#include "Event.h"

namespace Marx
{
	typedef int ControllerID;

	enum ControllerButton
	{
		ControllerButton_None = 0,
		ControllerButton_A,
		ControllerButton_B,
		ControllerButton_X,
		ControllerButton_Y,
		ControllerButton_Start,
		ControllerButton_Pause,
		ControllerButton_DPAD_Up,
		ControllerButton_DPAD_Down,
		ControllerButton_DPAD_Left,
		ControllerButton_DPAD_Right,
		ControllerButton_Thumb_Left,
		ControllerButton_Thumb_Right,
		ControllerButton_Shoulder_Left,
		ControllerButton_Shoulder_Right,
	};

	class MARX_API ControllerEvent : public Event
	{
	public:
		inline ControllerID getID() const { return m_cid; }
	protected:
		ControllerEvent(ControllerID cid)
			: m_cid(cid)
		{}
	protected:
		ControllerID m_cid;
	};

	class MARX_API ControllerConnectEvent : public ControllerEvent
	{
	public:
		ControllerConnectEvent(ControllerID cid)
			: ControllerEvent(cid)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerConnect[" << getID() << "]";
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagController | EventFlagDeviceConnection)
			EVENT_CLASS_TYPE(ControllerConnect)
	};

	class MARX_API ControllerDisconnectEvent : public ControllerEvent
	{
	public:
		ControllerDisconnectEvent(ControllerID cid)
			: ControllerEvent(cid)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerDisconnect[" << getID() << "]";
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagController | EventFlagDeviceConnection)
			EVENT_CLASS_TYPE(ControllerDisconnect)
	};

	class MARX_API ControllerTriggerMoveEvent : public ControllerEvent
	{
	public:
		ControllerTriggerMoveEvent(ControllerID cid, float delta)
			: ControllerEvent(cid), m_delta(delta)
		{}
	public:
		inline float getDelta() const { return m_delta; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerTriggerMove[" << getID() << "]: " << getDelta();
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagController | EventFlagControllerAnalog)
			EVENT_CLASS_TYPE(ControllerTriggerMove)
	private:
		float m_delta;
	};

	class MARX_API ControllerStickMoveEvent : public ControllerEvent
	{
	public:
		ControllerStickMoveEvent(ControllerID cid, float deltaX, float deltaY)
			: ControllerEvent(cid), m_deltaX(deltaX), m_deltaY(deltaY)
		{}
	public:
		inline float getDeltaX() const { return m_deltaX; }
		inline float getDeltaY() const { return m_deltaY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerStickMove[" << getID() << "]: " << getDeltaX() << ", " << getDeltaY();
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagController | EventFlagControllerAnalog)
			EVENT_CLASS_TYPE(ControllerStickMove)
	private:
		float m_deltaX;
		float m_deltaY;
	};

	class MARX_API ControllerButtonEvent : public ControllerEvent
	{
	public:
		inline ControllerButton getButton() const { return m_button; }

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagController | EventFlagControllerButton)
	protected:
		ControllerButtonEvent(ControllerID cid, ControllerButton button)
			: ControllerEvent(cid), m_button(button)
		{}
	protected:
		ControllerButton m_button;
	};

	class MARX_API ControllerButtonPressEvent : public ControllerButtonEvent
	{
	public:
		ControllerButtonPressEvent(ControllerID cid, ControllerButton button, int repeatCount)
			: ControllerButtonEvent(cid, button), m_repeatCount(repeatCount)
		{}
	public:
		inline int getRepeatCount() const { return m_repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerButtonPress[" << getID() << "]: " << getButton() << " (" << getRepeatCount() << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(ControllerButtonPress)
	private:
		int m_repeatCount;
	};

	class MARX_API ControllerButtonReleaseEvent : public ControllerButtonEvent
	{
	public:
		ControllerButtonReleaseEvent(ControllerID cid, ControllerButton button)
			: ControllerButtonEvent(cid, button)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerButtonRelease[" << getID() << "]: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(ControllerButtonRelease)
	};
}