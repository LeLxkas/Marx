#include "mxpch.h"
#include "RenderCommand.h"

#include "Marx/Platform/D3D11/D3D11RendererAPI.h"

namespace Marx
{
	RendererAPI* RenderCommand::s_rendererAPI = new D3D11RendererAPI();
}