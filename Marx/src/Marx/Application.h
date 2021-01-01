#pragma once

#include "Core.h"
#include "Window.h"
#include "Marx/LayerStack.h"
#include "Marx/Events/Event.h"
#include "Marx/Events/WindowEvents.h"

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
		static inline Application& get() { return *s_instance; }
		inline Window& getWindow() { return *m_pWindow; }
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		ImGuiLayer* m_pImGuiLayer;
		DISABLE_DLL_INTERFACE_WARN;
		std::unique_ptr<Window> m_pWindow;
		REENABLE_DLL_INTERFACE_WARN;
		bool m_running = true;
		LayerStack m_layerStack;
		// Temporary
		std::unique_ptr<class IndexBuffer> m_pIndexBuffer;
		std::unique_ptr<class Shader> m_pShader;
		std::unique_ptr<class VertexBuffer> m_pVertexBuffer;
		std::unique_ptr<class IndexBuffer> m_pSqIndexBuffer;
		std::unique_ptr<class VertexBuffer> m_pSqVertexBuffer;
	private:
		static Application* s_instance;
	};

	// To be defined by client
	Application* createApplication();
}