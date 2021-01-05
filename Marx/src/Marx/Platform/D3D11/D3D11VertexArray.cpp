#include "mxpch.h"
#include "D3D11VertexArray.h"

namespace Marx
{
	D3D11VertexArray::D3D11VertexArray()
	{}

	void D3D11VertexArray::bind() const
	{
		m_pVertexBuffer->bind();
		m_pIndexBuffer->bind();
	}

	void D3D11VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		m_pVertexBuffer = vertexBuffer;
	}

	void D3D11VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_pIndexBuffer = indexBuffer;
	}
	VertexBuffer* D3D11VertexArray::getVertexBuffer()
	{
		return m_pVertexBuffer.get();
	}
	IndexBuffer* D3D11VertexArray::getIndexBuffer()
	{
		return m_pIndexBuffer.get();
	}
}