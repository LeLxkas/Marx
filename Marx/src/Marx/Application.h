#pragma once

#include "Core.h"
#include "Window.h"
#include "Marx/LayerStack.h"
#include "Marx/Events/Event.h"
#include "Marx/Events/WindowEvents.h"

#include "Marx/Core/Timestep.h"

#include "Marx/ImGui/ImGuiLayer.h"

#include "mxpch.h"

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
	public:
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
	public:
		static inline Application* get() { return s_instance; }
		inline Window* getWindow() { return m_pWindow.get(); }
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		ImGuiLayer* m_pImGuiLayer;
		DISABLE_DLL_INTERFACE_WARN;
		std::unique_ptr<Window> m_pWindow;
		REENABLE_DLL_INTERFACE_WARN;
		bool m_running = true;
		LayerStack m_layerStack;
		Timestep m_timestep;
	private:
		static Application* s_instance;
	};

	// To be defined by client
	Application* createApplication();
}