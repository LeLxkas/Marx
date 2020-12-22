#pragma once

#include "Controller.h"
#include "XController.h"

namespace Marx
{
	class MARX_API ControllerManager
	{
	public:
		static void init(const EventCallbackFunc& callback);
		static void shutdown();
		static void onUpdate();
	public:
		static const Controller& getController(ControllerID id);
	private:
		static bool s_initialized;
		DISABLE_DLL_INTERFACE_WARN;
		static EventCallbackFunc s_eventCallback;
		REENABLE_DLL_INTERFACE_WARN;
		static Controller* s_controller[XUSER_MAX_COUNT];
	};
}