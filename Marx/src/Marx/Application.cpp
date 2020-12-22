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
			Window::onUpdate();
			ControllerManager::onUpdate();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	void Application::onEvent(Event& e)
	{
		MX_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));
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