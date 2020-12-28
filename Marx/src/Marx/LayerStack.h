#pragma once

#include "Marx/Core.h"
#include "Layer.h"

namespace Marx
{
	class MARX_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
	public:
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* layer);
	public:
		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
	private:
		DISABLE_DLL_INTERFACE_WARN;
		std::vector<Layer*> m_layers;
		REENABLE_DLL_INTERFACE_WARN;
		unsigned int m_layerInsertIndex = 0;
	};
}