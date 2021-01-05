#include "mxpch.h"

#include "Application.h"

#include "Marx/Log.h"
#include "Marx/Input/ControllerManager.h"

#include "Marx/Input.h"

namespace Marx
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		MX_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_pWindow.reset(Window::create());
		m_pWindow->setEventCallback(MX_BIND_EVENT_METHOD(Application::onEvent));

		m_pImGuiLayer = new ImGuiLayer;
		pushOverlay(m_pImGuiLayer);

		ControllerManager::init(MX_BIND_EVENT_METHOD(Application::onEvent));
	}

	Application::~Application()
	{
		ControllerManager::shutdown();
	}

	void Application::run()
	{
		static float rotation = 0.0f;

		while (m_running)
		{
			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_pImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onImGuiRender();
			m_pImGuiLayer->end();

			m_pWindow->onUpdate();

			ControllerManager::onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(MX_BIND_EVENT_METHOD(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		e.getWnd()->shutdown();
		if (e.getWnd()->getWndCount() == 0)
		{
			m_running = false;
		}
		return true;
	}
}