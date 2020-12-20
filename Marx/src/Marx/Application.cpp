#include "mxpch.h"

#include "Application.h"

#include "Marx/Log.h"

namespace Marx
{
	#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));

		m_window1 = std::unique_ptr<Window>(Window::create());
		m_window1->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
	}

	Application::~Application()
	{}

	void Application::run()
	{
		while (m_running)
		{
			m_window->onUpdate();
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