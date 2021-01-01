#pragma once

namespace Marx
{
	enum class RendererAPI
	{
		None = 0,
		D3D11 = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI getAPI() { return s_rendererAPI; }
	private:
		static RendererAPI s_rendererAPI;
	};
}