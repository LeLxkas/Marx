#pragma once

namespace Marx
{
	enum class ControllerButton
	{
		A = 0,
		B,
		X,
		Y,
		Start,
		Back,
		DPAD_Up,
		DPAD_Down,
		DPAD_Left,
		DPAD_Right,
		Thumb_Left,
		Thumb_Right,
		Shoulder_Left,
		Shoulder_Right,
		Count
	};

	enum class ControllerStick
	{
		Left = 0,
		Right
	};

	enum class ControllerTrigger
	{
		Left = 0,
		Right
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