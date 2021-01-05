#pragma once

#include "Marx/Renderer/Buffer.h"

#include "Marx/Platform/DX11/DX11Includes.h"
#include "Marx/Platform/Win32/Win32Includes.h"

namespace Marx
{
	static DXGI_FORMAT shaderDataTypeToDXGI_FORMAT(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None:   return DXGI_FORMAT_UNKNOWN; // Unknown but supported
		case ShaderDataType::Float1: return DXGI_FORMAT_R32_FLOAT;
		case ShaderDataType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShaderDataType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShaderDataType::Mat3:   return DXGI_FORMAT_UNKNOWN; // Unknown but supported
		case ShaderDataType::Mat4:   return DXGI_FORMAT_UNKNOWN; // Unknown but supported
		case ShaderDataType::Int1:   return DXGI_FORMAT_R32_SINT;
		case ShaderDataType::Int2:   return DXGI_FORMAT_R32G32_SINT;
		case ShaderDataType::Int3:   return DXGI_FORMAT_R32G32B32_SINT;
		case ShaderDataType::Int4:   return DXGI_FORMAT_R32G32B32A32_SINT;
		case ShaderDataType::Bool1:  return DXGI_FORMAT_UNKNOWN; // Unknown but supported
		}

		MX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT_UNKNOWN;
	}

	static std::string shaderDataTypeToHLSL_String(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None:   break; // Unsupported
		case ShaderDataType::Float1: return "float1";
		case ShaderDataType::Float2: return "float2";
		case ShaderDataType::Float3: return "float3";
		case ShaderDataType::Float4: return "float4";
		case ShaderDataType::Mat3:   return "float3x3";
		case ShaderDataType::Mat4:   return "float4x4";
		case ShaderDataType::Int1:   return "int1";
		case ShaderDataType::Int2:   return "int2";
		case ShaderDataType::Int3:   return "int3";
		case ShaderDataType::Int4:   return "int4";
		case ShaderDataType::Bool1:  return "bool1";
		}

		MX_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return "";
	}

	class D3D11VertexBuffer : public VertexBuffer
	{
	public:
		D3D11VertexBuffer(float* vertices, uint32_t size);
		virtual ~D3D11VertexBuffer();
	public:
		virtual void bind() const override;
		virtual void setLayout(const BufferLayout& layout) override;
	public:
		static std::vector<D3D11_INPUT_ELEMENT_DESC> genElementDesc(const BufferLayout& layout);
		static ID3DBlob* genDummyShader(const BufferLayout& layout);
	private:
		uint32_t m_stride;
		ComPtr<ID3D11Buffer> m_pVertexBuffer;
		ComPtr<ID3D11InputLayout> m_pInputLayout;
	};

	///////////////////////////////////////
	// ---------- IndexBuffer ---------- //
	///////////////////////////////////////

	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(uint32_t* indices, uint32_t count, PrimitiveType primType);
		virtual ~DX11IndexBuffer();
	public:
		virtual void bind() const override;
		virtual uint32_t getCount() const override { return m_count; }
	public:
		uint32_t m_count;
		ComPtr<ID3D11Buffer> m_pIndexBuffer;
		D3D11_PRIMITIVE_TOPOLOGY m_primitiveTopology;
	};

	static D3D11_PRIMITIVE_TOPOLOGY primitiveTypeToD3D11PrimitiveTopology(IndexBuffer::PrimitiveType primType)
	{
		using PT = IndexBuffer::PrimitiveType;
		switch (primType)
		{
		case PT::None: return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
		case PT::PointList: return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		case PT::LineList: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		case PT::LineStrip: return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		case PT::TriangleList: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		case PT::TriangleStrip: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		}

		MX_CORE_ASSERT(false, "Unknown PrimitiveType!");
		return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}

	//////////////////////////////////////////
	// ---------- ConstantBuffer ---------- //
	//////////////////////////////////////////

	class D3D11ConstantBuffer : public ConstantBuffer
	{
	public:
		D3D11ConstantBuffer(uint32_t slot, uint32_t size, const void* data);
	public:
		virtual void bind() const override;
		virtual void update(const void* data) override;
	private:
		uint32_t m_slot;
		uint32_t m_size;
		ComPtr<ID3D11Buffer> m_pBuffer;
	};
}