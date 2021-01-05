#include "mxpch.h"

#include "D3D11Shader.h"

#include "Marx/Platform/D3D11/D3D11InfoManager.h"
#include "Marx/Platform/D3D11/D3D11InfoException.h"
#include "Marx/Platform/D3D11/D3D11ExceptionMacros.h"

#include "Marx/Platform/D3D11/D3D11GraphicsContext.h"

namespace Marx
{
	Shader* Shader::create(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		return new D3D11Shader(vertexSrc, pixelSrc);
	}

	D3D11Shader::D3D11Shader(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		MX_DEBUG_HR_DECL;

		ComPtr<ID3DBlob> pVSCode, pPSCode;
		MX_VERIFY_THROW_HR_INFO(compileShaderFromSrc(vertexSrc, "vs_5_0", pVSCode.GetAddressOf()));
		MX_VERIFY_THROW_HR_INFO(compileShaderFromSrc(pixelSrc, "ps_5_0", pPSCode.GetAddressOf()));
		MX_VERIFY_THROW_HR_INFO(D3D11GraphicsContext::D3D11Manager::getDevice()->CreateVertexShader(pVSCode->GetBufferPointer(), pVSCode->GetBufferSize(), NULL, m_pVertexShader.GetAddressOf()));
		MX_VERIFY_THROW_HR_INFO(D3D11GraphicsContext::D3D11Manager::getDevice()->CreatePixelShader(pPSCode->GetBufferPointer(), pPSCode->GetBufferSize(), NULL, m_pPixelShader.GetAddressOf()));
	}

	D3D11Shader::~D3D11Shader()
	{}

	void D3D11Shader::bind() const
	{
		D3D11GraphicsContext::D3D11Manager::getContext()->VSSetShader(m_pVertexShader.Get(), 0, 0);
		D3D11GraphicsContext::D3D11Manager::getContext()->PSSetShader(m_pPixelShader.Get(), 0, 0);
	}

	HRESULT D3D11Shader::compileShaderFromSrc(const std::string& src, const char* pTarget, ID3DBlob** ppBytecode)
	{
		ComPtr<ID3DBlob> pErrBlob = nullptr;
		UINT flags = 0;
	#ifdef MX_DEBUG
		flags |= D3DCOMPILE_DEBUG;
	#endif
		HRESULT hr = D3DCompile(
			src.c_str(), src.size(), NULL,
			NULL, NULL, "main", pTarget,
			flags, 0, ppBytecode, pErrBlob.GetAddressOf()
		);
		if (pErrBlob)
		{
			std::string errString((char*)pErrBlob->GetBufferPointer(), pErrBlob->GetBufferSize());
			MX_CORE_ERROR("{0}", errString);
		}
		return hr;
	}
}