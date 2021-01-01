#pragma once

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
		class ComPtr<IDXGIInfoQueue> m_pInfoQueue;
	private:
		static D3D11InfoManager* s_pInfoMan;
	};
}