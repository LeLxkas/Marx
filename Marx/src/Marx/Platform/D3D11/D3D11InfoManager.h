#pragma once

#include "Marx/Platform/DX11/DX11Includes.h"
#include "Marx/Platform/Win32/Win32Includes.h"

namespace Marx
{
	class D3D11InfoManager
	{
	private:
		D3D11InfoManager();
	public:
		static D3D11InfoManager* get() { return s_pInfoMan; }
	public:
		void set() { m_setIndex = getMsgCount(); }
		std::vector<std::string> getMessages();
	private:
		UINT64 getMsgCount();
		std::string getMessage(UINT64 index);
	private:
		UINT64 m_setIndex;
		ComPtr<IDXGIInfoQueue> m_pInfoQueue;
	private:
		static D3D11InfoManager* s_pInfoMan;
	};
}