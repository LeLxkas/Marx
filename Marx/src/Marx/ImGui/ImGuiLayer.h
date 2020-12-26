#pragma once

#include "Marx/Layer.h"
#include "Marx/Events/MouseEvents.h"
#include "Marx/Events/WindowEvents.h"
#include "Marx/Events/KeyboardEvents.h"

namespace Marx
{
	class MARX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
	public:
		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		bool onMouseButtonPressEvent(MouseButtonPressEvent& e);
		bool onMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
		bool onMouseMoveEvent(MouseMoveEvent& e);
		bool onMouseScrollEvent(MouseScrollEvent& e);
		bool onMouseHScrollEvent(MouseHScrollEvent& e);
		bool onKeyPressEvent(KeyPressEvent& e);
		bool onKeyReleaseEvent(KeyReleaseEvent& e);
		bool onKeyTypeEvent(KeyTypeEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
	private:
		std::chrono::high_resolution_clock m_clock;
		DISABLE_DLL_INTERFACE_WARN;
		std::chrono::steady_clock::time_point m_time;
		REENABLE_DLL_INTERFACE_WARN;
	};
}