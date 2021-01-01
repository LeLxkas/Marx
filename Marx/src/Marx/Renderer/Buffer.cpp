#include "mxpch.h"
#include "Buffer.h"

#include "Renderer.h"

#ifdef MX_PLATFORM_WINDOWS
#include "Marx/Platform/D3D11/D3D11Buffer.h"
#endif

namespace Marx
{
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			MX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::D3D11:
#ifdef MX_PLATFORM_WINDOWS
			return new D3D11VertexBuffer(vertices, size);
#else
			MX_CORE_ASSERT(false, "RendererAPI::DX11 is not supported!");
			return nullptr;
#endif
		}

		MX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	///////////////////////////////////////
	// ---------- IndexBuffer ---------- //
	///////////////////////////////////////

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
    {
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:
			MX_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::D3D11:
#ifdef MX_PLATFORM_WINDOWS
			return new DX11IndexBuffer(indices, count);
#else
			MX_CORE_ASSERT(false, "RendererAPI::DX11 is not supported!");
			return nullptr;
#endif
		}

		MX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}