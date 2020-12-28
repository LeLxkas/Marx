#include "mxpch.h"
#include "DX11InfoManager.h"

#include "Marx/Exceptions/ExceptionMacros.h"
#include "Marx/Platform/DX11/DX11InfoException.h"
#include "Marx/Platform/DX11/DX11ExceptionMacros.h"

namespace Marx
{
	DX11InfoManager* DX11InfoManager::s_pInfoMan = new DX11InfoManager;

	DX11InfoManager::DX11InfoManager()
	{
		using GetDebugInterfaceFunc = HRESULT __stdcall(const IID&, void**);

		HMODULE dxgidebug = LoadLibraryEx("dxgidebug.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
		auto getDebugInterface = (GetDebugInterfaceFunc*)GetProcAddress(dxgidebug, "DXGIGetDebugInterface");

		getDebugInterface(__uuidof(IDXGIInfoQueue), (void**)m_pInfoQueue.GetAddressOf());
	}

	std::vector<std::string> DX11InfoManager::getMessages()
	{
		std::vector<std::string> msgs;
		UINT64 maxIndex = getMsgCount();
		for (UINT64 i = m_setIndex; i < maxIndex; ++i)
		{
			msgs.push_back(getMessage(i));
		}
		return msgs;
	}

	UINT64 DX11InfoManager::getMsgCount()
	{
		return m_pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL);
	}

	std::string DX11InfoManager::getMessage(UINT64 index)
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