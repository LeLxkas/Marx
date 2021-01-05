#pragma once

#include "Marx/Renderer/VertexArray.h"

namespace Marx
{
	class D3D11VertexArray : public VertexArray
	{
	public:
		D3D11VertexArray();
		virtual ~D3D11VertexArray() {}
	public:
		virtual void bind() const override;
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		virtual VertexBuffer* getVertexBuffer() override;
		virtual IndexBuffer* getIndexBuffer() override;
	private:
		std::shared_ptr<VertexBuffer> m_pVertexBuffer;
		std::shared_ptr<IndexBuffer> m_pIndexBuffer;
	};
}