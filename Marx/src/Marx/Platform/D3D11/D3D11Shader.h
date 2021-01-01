#pragma once

#include <string>

#include "Marx/Renderer/Shader.h"

namespace Marx
{
	class D3D11Shader : public Shader
	{
	public:
		D3D11Shader(const std::string& vertexSrc, const std::string& pixelSrc);
		~D3D11Shader();
	public:
		virtual void bind() const override;
		inline ID3D11VertexShader* getVertexShader() const { return m_pVertexShader.Get(); }
		inline ID3D11PixelShader* getPixelShader() const { return m_pPixelShader.Get(); }
	public:
		static HRESULT compileShaderFromSrc(const std::string& src, const char* pTarget, ID3DBlob** ppBytecode);
	private:
		ComPtr<ID3D11PixelShader> m_pPixelShader;
		ComPtr<ID3D11VertexShader> m_pVertexShader;
	};
}