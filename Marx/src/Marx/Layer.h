#pragma once

#include "Marx/Core.h"
#include "Marx/Events/Event.h"
#include "Marx/Core/Timestep.h"

namespace Marx
{
	class MARX_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getDebugName() const { return m_debugName; }
	protected:
		DISABLE_DLL_INTERFACE_WARN;
		std::string m_debugName;
		REENABLE_DLL_INTERFACE_WARN;
	};
}