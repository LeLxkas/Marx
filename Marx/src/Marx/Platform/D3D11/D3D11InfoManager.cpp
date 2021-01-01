#include "mxpch.h"
#include "D3D11InfoManager.h"

#include "Marx/Exceptions/ExceptionMacros.h"
#include "Marx/Platform/D3D11/D3D11InfoException.h"
#include "Marx/Platform/D3D11/D3D11ExceptionMacros.h"

namespace Marx
{
	D3D11InfoManager* D3D11InfoManager::s_pInfoMan = new D3D11InfoManager;

	D3D11InfoManager::D3D11InfoManager()
	{
		using GetDebugInterfaceFunc = HRESULT __stdcall(const IID&, void**);

		HMODULE dxgidebug = LoadLibraryEx("dxgidebug.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
		auto getDebugInterface = (GetDebugInterfaceFunc*)GetProcAddress(dxgidebug, "DXGIGetDebugInterface");

		getDebugInterface(__uuidof(IDXGIInfoQueue), (void**)m_pInfoQueue.GetAddressOf());
	}

	std::vector<std::string> D3D11InfoManager::getMessages()
	{
		std::vector<std::string> msgs;
		UINT64 maxIndex = getMsgCount();
		for (UINT64 i = m_setIndex; i < maxIndex; ++i)
		{
			msgs.push_back(getMessage(i));
		}
		return msgs;
	}

	UINT64 D3D11InfoManager::getMsgCount()
	{
		return m_pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL);
	}

	std::string D3D11InfoManager::getMessage(UINT64 index)
	{
		MX_DEBUG_HR_DECL;

		size_t msgLen = 0;
		MX_VERIFY_THROW_HR(
			m_pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, 0, NULL,&msgLen)
		);

		DXGI_INFO_QUEUE_MESSAGE* pMsg = (DXGI_INFO_QUEUE_MESSAGE*)malloc(msgLen);
		MX_VERIFY_THROW_HR(
			m_pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, 0, pMsg, &msgLen)
		);

		std::string msg(pMsg->pDescription, pMsg->DescriptionByteLength);
		free(pMsg);

		return msg;
	}
}