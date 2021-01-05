#pragma once

#include "Marx/Renderer/RendererAPI.h"

namespace Marx
{
	class D3D11RendererAPI : public RendererAPI
	{
	public:
		virtual void setClearColor(float r, float g, float b, float a) override;
		virtual void clear() override;
		
		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	private:
		float m_clearColor[4];
	};
}