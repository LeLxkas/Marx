#include "mxpch.h"
#include "ControllerManager.h"

namespace Marx
{
	bool ControllerManager::s_initialized = false;
	EventCallbackFunc ControllerManager::s_eventCallback;
	Controller* ControllerManager::s_controller[XUSER_MAX_COUNT];

	void ControllerManager::init(const EventCallbackFunc& callback)
	{
		MX_ASSERT(!s_initialized, "ControllerManager already initialized!");

		s_eventCallback = callback;

		for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			s_controller[i] = new XController(i, i);
			s_controller[i]->setEventCallback(s_eventCallback);
		}

		s_initialized = true;
	}

	void ControllerManager::shutdown()
	{
		MX_ASSERT(s_initialized, "ControllerManager is not initialized!");
		for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			delete s_controller[i];
		}

		s_initialized = false;
	}

	void ControllerManager::onUpdate()
	{
		for (int i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			s_controller[i]->onUpdate();
		}
	}
	const Controller& ControllerManager::getController(ControllerID id)
	{
		return *s_controller[id];
	}
}
