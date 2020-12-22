#pragma once

namespace Marx
{
	enum ControllerButton
	{
		ControllerButton_A = 0,
		ControllerButton_B,
		ControllerButton_X,
		ControllerButton_Y,
		ControllerButton_Start,
		ControllerButton_Back,
		ControllerButton_DPAD_Up,
		ControllerButton_DPAD_Down,
		ControllerButton_DPAD_Left,
		ControllerButton_DPAD_Right,
		ControllerButton_Thumb_Left,
		ControllerButton_Thumb_Right,
		ControllerButton_Shoulder_Left,
		ControllerButton_Shoulder_Right,
		ControllerButton_Count
	};

	enum ControllerStick
	{
		ControllerStick_Left = 0,
		ControllerStick_Right
	};

	enum ControllerTrigger
	{
		ControllerTrigger_Left = 0,
		ControllerTrigger_Right
	};

	typedef char ControllerButtonState;
	#define ControllerButtonState_Up FLAG(0)
	#define ControllerButtonState_Down FLAG(1)
	#define ControllerButtonState_Repeat FLAG(2)

	struct ControllerStickState
	{
		float x, y;
	};
}