#pragma once

#include "Marx/Core.h"

namespace Marx
{
	class MARX_API Input
	{
	public:
		inline static bool isKeyPressed(int keyCode) { return s_pInstance->isKeyPressedImpl(keyCode); }
		inline static bool isMouseButtonPressed(int button) { return s_pInstance->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> getMousePos() { return s_pInstance->getMousePosImpl(); }
		inline static float getMouseX() { return s_pInstance->getMouseXImpl(); }
		inline static float getMouseY() { return s_pInstance->getMouseYImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keyCode) const = 0;
		virtual bool isMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float> getMousePosImpl() const = 0;
		virtual float getMouseXImpl() const = 0;
		virtual float getMouseYImpl() const = 0;
	private:
		static Input* s_pInstance;
	};
}