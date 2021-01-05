#pragma once

#include "Marx/Input.h"

namespace Marx
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keyCode) const override;
		virtual bool isMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> getMousePosImpl() const override;
		virtual float getMouseXImpl() const override;
		virtual float getMouseYImpl() const override;
	};
}