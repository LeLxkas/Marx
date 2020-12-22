#pragma once

#include <Xinput.h>

#include "Controller.h"

#pragma comment(lib, "XInput.lib")

namespace Marx
{
	class MARX_API XController : public Controller
	{
	public:
		XController(ControllerID id, DWORD uid)
			: Controller(id), m_uid(uid), m_pStateNew(&m_states[0]), m_pStateOld(&m_states[1]), m_cState(), m_states()
		{}
	public:
		bool onUpdate() override;
		ControllerButtonState buttonState(ControllerButton btn) const override { return m_cState.button[btn]; }
		ControllerStickState stickState(ControllerStick stick) const override { return m_cState.stick[stick]; }
		float triggerState(ControllerTrigger trigger) const override { return m_cState.trigger[trigger]; }
	public:
		ControllerType getType() const override { return ControllerType_XInput; }
	private:
		DWORD m_uid;
		XINPUT_STATE* m_pStateNew;
		XINPUT_STATE* m_pStateOld;
		XINPUT_STATE m_states[2];
		struct ControllerState
		{
			ControllerButtonState button[ControllerButton_Count];
			float trigger[2];
			ControllerStickState stick[2];
		} m_cState;
	};
}