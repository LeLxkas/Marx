#include "mxpch.h"
#include "D3D11Buffer.h"

#include "D3D11GraphicsContext.h"
#include "Marx/Platform/D3D11/D3D11InfoManager.h"
#include "Marx/Platform/D3D11/D3D11InfoException.h"
#include "Marx/Platform/D3D11/D3D11ExceptionMacros.h"

#include "Marx/Platform/D3D11/D3D11Shader.h"

namespace Marx
{
	D3D11VertexBuffer::D3D11VertexBuffer(float* vertices, uint32_t size)
	{
		MX_DEBUG_HR_DECL;

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = size;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vbInitData;
		vbInitData.pSysMem = vertices;
		vbInitData.SysMemPitch = 0;
		vbInitData.SysMemSlicePitch = 0;
		MX_VERIFY_THROW_HR_INFO(
			D3D11GraphicsContext::D3D11Manager::getDevice().CreateBuffer(
				&vertexBufferDesc, &vbInitData,
				m_pVertexBuffer.GetAddressOf()
			)
		);
	}

	D3D11VertexBuffer::~D3D11VertexBuffer()
	{}

	void D3D11VertexBuffer::bind() const
	{
		uint32_t offset = 0;
		D3D11GraphicsContext::D3D11Manager::getContext().IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &m_stride, &offset);
		D3D11GraphicsContext::D3D11Manager::getContext().IASetInputLayout(m_pInputLayout.Get());
	}

	void D3D11VertexBuffer::setLayout(const BufferLayout& layout)
	{
		MX_DEBUG_HR_DECL;

		auto elementDesc = genElementDesc(layout);
		ComPtr<ID3DBlob> dummyShader = genDummyShader(layout);

		MX_VERIFY_THROW_HR_INFO(
			D3D11GraphicsContext::D3D11Manager::getDevice().CreateInputLayout(
				elementDesc.data(), (UINT)elementDesc.size(),
				dummyShader->GetBufferPointer(), dummyShader->GetBufferSize(),
				m_pInputLayout.GetAddressOf()
			)
		);
		m_stride = layout.getStride();
	}

	std::vector<D3D11_INPUT_ELEMENT_DESC> D3D11VertexBuffer::genElementDesc(const BufferLayout& layout)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc;
		for (auto& element : layout)
		{
			elementDesc.push_back(
				{ element.name.c_str(), 0, shaderDataTypeToDXGI_FORMAT(element.type), 0, element.offset, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			);
		}
		return elementDesc;
	}

	ID3DBlob* D3D11VertexBuffer::genDummyShader(const BufferLayout& layout)
	{
		MX_DEBUG_HR_DECL;

		std::string shaderSrc;
		shaderSrc.append("struct VS_INPUT {\n");
		uint32_t index = 0;
		for (auto& element : layout)
		{
			shaderSrc.append(shaderDataTypeToHLSL_String(element.type));
			shaderSrc.append(" elem" + std::to_string(index) + " : " + element.name + ";\n");
			++index;
		}
		shaderSrc.append("};\n");
		shaderSrc.append("float4 main(VS_INPUT inp) : SV_POSITION { return float4(0.0f, 0.0f, 0.0f, 0.0f); }");

		ID3DBlob* pShader;
		MX_VERIFY_THROW_HR_INFO(D3D11Shader::compileShaderFromSrc(shaderSrc, "vs_5_0", &pShader));
		return pShader;
	}

	///////////////////////////////////////
	// ---------- IndexBuffer ---------- //
	///////////////////////////////////////
	
	DX11IndexBuffer::DX11IndexBuffer(uint32_t* indices, uint32_t count)
		: m_count(count)
	{
		MX_DEBUG_HR_DECL;

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * count;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA ibInitData;
		ibInitData.pSysMem = indices;
		ibInitData.SysMemPitch = 0;
		ibInitData.SysMemSlicePitch = 0;

		MX_VERIFY_THROW_HR_INFO(
			D3D11GraphicsContext::D3D11Manager::getDevice().CreateBuffer(
				&indexBufferDesc, &ibInitData, m_pIndexBuffer.GetAddressOf()
			)
		);
	}

	DX11IndexBuffer::~DX11IndexBuffer()
	{}

	void DX11IndexBuffer::bind() const
	{
		D3D11GraphicsContext::D3D11Manager::getContext().IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
}