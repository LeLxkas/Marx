#pragma once

#include <Xinput.h>

#include "Marx/Input/Controller.h"

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
		ControllerButtonState buttonState(ControllerButton btn) const override { return m_cState.button[(uint32_t)btn]; }
		ControllerStickState stickState(ControllerStick stick) const override { return m_cState.stick[(uint32_t)stick]; }
		float triggerState(ControllerTrigger trigger) const override { return m_cState.trigger[(uint32_t)trigger]; }
	public:
		ControllerType getType() const override { return ControllerType::XInput; }
	private:
		DWORD m_uid;
		XINPUT_STATE* m_pStateNew;
		XINPUT_STATE* m_pStateOld;
		XINPUT_STATE m_states[2];
		struct ControllerState
		{
			ControllerButtonState button[(uint32_t)ControllerButton::Count];
			float trigger[2];
			ControllerStickState stick[2];
		} m_cState;
	};
}