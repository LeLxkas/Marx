#include "mxpch.h"

#include "Application.h"

#include "Marx/Log.h"
#include "Marx/Input/ControllerManager.h"

namespace Marx
{
	#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));

		ControllerManager::init(BIND_EVENT_FUNC(Application::onEvent));
	}

	Application::~Application()
	{
		ControllerManager::shutdown();
	}

	void Application::run()
	{
		while (m_running)
		{

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			Window::onUpdate();
			ControllerManager::onUpdate();

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

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
		if (Window::getCount() == 0)
		{
			m_running = false;
		}
		return true;
	}
}