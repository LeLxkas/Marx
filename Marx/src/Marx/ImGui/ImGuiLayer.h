#pragma once

#include "Marx/Layer.h"
#include "Marx/Events/MouseEvents.h"
#include "Marx/Events/WindowEvents.h"
#include "Marx/Events/KeyboardEvents.h"

#include <chrono>

namespace Marx
{
	class MARX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
	public:
		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;
	public:
		void begin();
		void end();
	private:
		std::chrono::high_resolution_clock m_clock;
		DISABLE_DLL_INTERFACE_WARN;
		std::chrono::steady_clock::time_point m_time;
		REENABLE_DLL_INTERFACE_WARN;
	};
}