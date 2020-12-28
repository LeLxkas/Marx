#include "mxpch.h"
#include "LayerStack.h"

namespace Marx
{
	LayerStack::LayerStack()
	{}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex++, layer);
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);

		MX_CORE_ASSERT(it != m_layers.end(), "Could not find layer in layerstack!");

		m_layers.erase(it);
		--m_layerInsertIndex;
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);

		MX_CORE_ASSERT(it != m_layers.end(), "Could not find overlay in layerstack!");

		m_layers.erase(it);
	}
}
