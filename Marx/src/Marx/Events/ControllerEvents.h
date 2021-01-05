#pragma once

#include "Event.h"
#include "Marx/Input/ControllerInputs.h"

namespace Marx
{
	typedef int ControllerID;

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
		ControllerTriggerMoveEvent(ControllerID cid, ControllerTrigger trigger, float delta)
			: ControllerEvent(cid), m_trigger(trigger), m_delta(delta)
		{}
	public:
		inline ControllerTrigger getTrigger() const { return m_trigger; }
		inline float getDelta() const { return m_delta; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerTriggerMove[" << getID() << "]: " << (uint32_t)getTrigger() << " (" << getDelta() << ")";
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagController | EventFlagControllerAnalog)
			EVENT_CLASS_TYPE(ControllerTriggerMove)
	private:
		ControllerTrigger m_trigger;
		float m_delta;
	};

	class MARX_API ControllerStickMoveEvent : public ControllerEvent
	{
	public:
		ControllerStickMoveEvent(ControllerID cid, ControllerStick stick, ControllerStickState sState)
			: ControllerEvent(cid), m_stick(stick), m_sState(sState)
		{}
	public:
		inline ControllerStick getStick() const { return m_stick; }
		inline ControllerStickState getState() const { return m_sState; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerStickMove[" << getID() << "]: " << (uint32_t)getStick() << " (" << getState().x << ", " << getState().y << ")";
			return ss.str();
		}

		EVENT_CLASS_FLAGS(EventFlagInput | EventFlagController | EventFlagControllerAnalog)
			EVENT_CLASS_TYPE(ControllerStickMove)
	private:
		ControllerStick m_stick;
		ControllerStickState m_sState;
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
		ControllerButtonPressEvent(ControllerID cid, ControllerButton button)
			: ControllerButtonEvent(cid, button)
		{}
	public:
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "ControllerButtonPress[" << getID() << "]: " << (uint32_t)getButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(ControllerButtonPress)
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
			ss << "ControllerButtonRelease[" << getID() << "]: " << (uint32_t)m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(ControllerButtonRelease)
	};
}