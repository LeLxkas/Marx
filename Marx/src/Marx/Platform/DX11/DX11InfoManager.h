#pragma once

#include "mxpch.h"

namespace Marx
{
	class DX11InfoManager
	{
	private:
		DX11InfoManager();
	public:
		static DX11InfoManager* get() { return s_pInfoMan; }
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
		static DX11InfoManager* s_pInfoMan;
	};
}