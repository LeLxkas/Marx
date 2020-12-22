#include "mxpch.h"
#include "XController.h"

namespace Marx
{
	bool XController::onUpdate()
	{
		static constexpr int convTable[ControllerButton_Count]
			= {
			0x1000, 0x2000, 0x4000, 0x8000,
			0x0010, 0x0020,
			0x0001, 0x0002, 0x0004, 0x0008,
			0x0040, 0x0080, 0x0100, 0x0200
		};

		std::swap(m_pStateNew, m_pStateOld);

		if (XInputGetState(m_uid, m_pStateNew) == ERROR_DEVICE_NOT_CONNECTED)
		{
			if (m_isConnected)
			{
				m_isConnected = false;
				ControllerDisconnectEvent event(m_id);
				m_eventCallback(event);
			}
			return false; // Device disconnected, can be removed from pool
		}

		if (!m_isConnected)
		{
			m_isConnected = true;
			ControllerConnectEvent event(m_id);
			m_eventCallback(event);
		}

		if (m_pStateNew->dwPacketNumber != m_pStateOld->dwPacketNumber) // Device state has changed
		{
			XINPUT_GAMEPAD& gpNew = m_pStateNew->Gamepad;
			XINPUT_GAMEPAD& gpOld = m_pStateOld->Gamepad;

			// Get changed buttons
			WORD diff = gpNew.wButtons ^ gpOld.wButtons;

			// Loop over all buttons and update them appropiately
			for (int i = 0; i < ControllerButton_Count; ++i)
			{
				if (HAS_FLAG(diff, convTable[i])) // Button state changed
				{
					if (HAS_FLAG(gpNew.wButtons, convTable[i])) // Button is pressed
					{
						SET_FLAG(m_cState.button[i], ControllerButtonState_Down);
						ControllerButtonPressEvent event(m_id, (ControllerButton)i);
						m_eventCallback(event);
					}
					else // Button is released
					{
						SET_FLAG(m_cState.button[i], ControllerButtonState_Up);
						ControllerButtonReleaseEvent event(m_id, (ControllerButton)i);
						m_eventCallback(event);
					}
				}
				else // No state change
				{
					// Update state to repeat
					ADD_FLAG(m_cState.button[i], ControllerButtonState_Repeat);
				}
			}

			if (gpNew.bLeftTrigger != gpOld.bLeftTrigger) // Left trigger moved
			{
				m_cState.trigger[ControllerTrigger_Left] = BYTE_TO_NORM_FLOAT(gpNew.bLeftTrigger);
				ControllerTriggerMoveEvent event(m_id, ControllerTrigger_Left, m_cState.trigger[ControllerTrigger_Left]);
				m_eventCallback(event);
			}
			if (gpNew.bRightTrigger != gpOld.bRightTrigger) // Right trigger moved
			{
				m_cState.trigger[ControllerTrigger_Right] = BYTE_TO_NORM_FLOAT(gpNew.bRightTrigger);
				ControllerTriggerMoveEvent event(m_id, ControllerTrigger_Right, m_cState.trigger[ControllerTrigger_Right]);
				m_eventCallback(event);
			}

			if (gpNew.sThumbLX != gpOld.sThumbLX ||
				gpNew.sThumbLY != gpOld.sThumbLY) // Left stick moved
			{
				m_cState.stick[ControllerStick_Left].x = SHORT_TO_NORM_FLOAT(gpNew.sThumbLX);
				m_cState.stick[ControllerStick_Left].y = SHORT_TO_NORM_FLOAT(gpNew.sThumbLY);
				ControllerStickMoveEvent event(m_id, ControllerStick_Left, m_cState.stick[ControllerStick_Left]);
				m_eventCallback(event);
			}
			if (gpNew.sThumbRX != gpOld.sThumbRX ||
				gpNew.sThumbRY != gpOld.sThumbRY) // Left stick moved
			{
				m_cState.stick[ControllerStick_Right].x = SHORT_TO_NORM_FLOAT(gpNew.sThumbRX);
				m_cState.stick[ControllerStick_Right].y = SHORT_TO_NORM_FLOAT(gpNew.sThumbRY);
				ControllerStickMoveEvent event(m_id, ControllerStick_Right, m_cState.stick[ControllerStick_Right]);
				m_eventCallback(event);
			}
		}
		else // Device state has not changed
		{
			// Set all buttons to repeat
			for (int i = 0; i < ControllerButton_Count; ++i)
			{
				ADD_FLAG(m_cState.button[i], ControllerButtonState_Repeat);
			}
		}

		return true; // Device still active
	}
}