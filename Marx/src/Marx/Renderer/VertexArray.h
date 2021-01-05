#pragma once

#include "Buffer.h"

namespace Marx
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
	public:
		virtual void bind() const = 0;
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
		virtual VertexBuffer* getVertexBuffer() = 0;
		virtual IndexBuffer* getIndexBuffer() = 0;
	public:
		static VertexArray* create();
	};
}