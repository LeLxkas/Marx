#pragma once

#include "RendererAPI.h"

namespace Marx
{
	class RenderCommand
	{
	public:
		inline static void setClearColor(float r, float g, float b, float a) { s_rendererAPI->setClearColor(r, g, b, a); }
		inline static void clear() { s_rendererAPI->clear(); }
		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_rendererAPI->drawIndexed(vertexArray); }
	private:
		static RendererAPI* s_rendererAPI;
	};
}