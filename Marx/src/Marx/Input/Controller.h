#pragma once

#include "Marx/Events/ControllerEvents.h"

namespace Marx
{
	#define BYTE_TO_NORM_FLOAT(b) (((float)b) / 255)
	#define SHORT_TO_NORM_FLOAT(s) (((float)s) / 32767)

	enum ControllerType
	{
		ControllerType_None = 0,
		ControllerType_XInput,
		ControllerType_DInput
	};

	class MARX_API Controller
	{
	public:
		Controller(ControllerID id)
			: m_id(id)
		{}
	public:
		ControllerID getID() const { return m_id; }
		void setEventCallback(const EventCallbackFunc& callback) const { m_eventCallback = callback; }
		// Returnvalue is zero when the controller is not connected.
		virtual bool onUpdate() = 0;
		virtual ControllerButtonState buttonState(ControllerButton btn) const = 0;
		virtual ControllerStickState stickState(ControllerStick stick) const = 0;
		virtual float triggerState(ControllerTrigger trigger) const = 0;
	public:
		virtual ControllerType getType() const = 0;
	protected:
		ControllerID m_id;
		bool m_isConnected = false;
		DISABLE_DLL_INTERFACE_WARN;
		mutable EventCallbackFunc m_eventCallback;
		REENABLE_DLL_INTERFACE_WARN;
	};
}