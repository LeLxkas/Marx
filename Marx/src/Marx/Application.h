#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Marx/Events/WindowEvents.h"

namespace Marx
{
	class MARX_API Application
	{
	public:
		Application();
		virtual ~Application();
	public:
		void run();
		void onEvent(Event& e);
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		DISABLE_DLL_INTERFACE_WARN;
		std::unique_ptr<Window> m_window;
		REENABLE_DLL_INTERFACE_WARN;
		bool m_running = true;
	};

	// To be defined by client
	Application* createApplication();
}