#include "mxpch.h"
#include "D3D11RendererAPI.h"

#include "D3D11GraphicsContext.h"

namespace Marx
{
	void D3D11RendererAPI::setClearColor(float r, float g, float b, float a)
	{
		m_clearColor[0] = r;
		m_clearColor[1] = g;
		m_clearColor[2] = b;
		m_clearColor[3] = a;
	}

	void D3D11RendererAPI::clear()
	{
		D3D11GraphicsContext::get()->clear(m_clearColor);
	}

	void D3D11RendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		D3D11GraphicsContext::D3D11Manager::getContext()->DrawIndexed(vertexArray->getIndexBuffer()->getCount(), 0, 0);
	}
}