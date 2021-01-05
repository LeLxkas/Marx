#pragma once

#include "Marx/Renderer/GraphicsContext.h"

#include "Marx/Platform/DX11/DX11Includes.h"
#include "Marx/Platform/Win32/Win32Includes.h"

namespace Marx
{
	class D3D11GraphicsContext : public GraphicsContext
	{
	public:
		D3D11GraphicsContext(HWND wndHandle);
		~D3D11GraphicsContext();
	public:
		virtual void init() override;
		virtual void shutdown() override;
		virtual void clear(float color[4]) override;
		virtual void swapBuffers() override;
		virtual void onResize(unsigned int width, unsigned int height);
	public:
		static GraphicsContext* get(uint32_t index = 0) { return s_contexts[index]; }
		static uint32_t getCount() { return (uint32_t)s_contexts.size(); }
	private:
		void present(bool vSyncEnabled);
		void createSwapChain();
		void createRenderTargetView();
		void createDepthStencil();
		void createDepthStencilView();
		void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		inline void setViewport() { D3D11Manager::getContext()->RSSetViewports(1, &m_viewport); }
		inline void unsetRenderTarget() { ID3D11RenderTargetView* nullViews[] = { nullptr }; D3D11Manager::getContext()->OMSetRenderTargets(1, nullViews, NULL); }
		inline void setRenderTarget() { D3D11Manager::getContext()->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get()); }
	private:
		DISABLE_DLL_INTERFACE_WARN;
		ComPtr<IDXGISwapChain> m_pSwapChain;
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
		ComPtr<ID3D11Texture2D> m_pDepthStencil;
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
		REENABLE_DLL_INTERFACE_WARN;
		D3D11_VIEWPORT m_viewport;
	private:
		HWND m_wndHandle;
		unsigned int m_width;
		unsigned int m_height;
		bool m_initialized = false;
	private:
		static std::vector<D3D11GraphicsContext*> s_contexts;
	public:
		class D3D11Manager
		{
		public:
			static void init();
			static void shutdown();
		public:
			inline static ID3D11Device* getDevice() { return s_pDevice.Get(); }
			inline static ID3D11DeviceContext* getContext() { return s_pContext.Get(); }
			static IDXGIAdapter* getAdapter();
			static IDXGIFactory* getFactory();
		public:
			inline static void flushContext() { s_pContext->Flush(); }
		private:
			inline static unsigned int s_initialized = 0;
		private:
			inline static ComPtr<ID3D11Device> s_pDevice;
			inline static ComPtr<ID3D11DeviceContext> s_pContext;
		};
	};
}