#include "mxpch.h"

#include "Application.h"

#include "Marx/Log.h"
#include "Marx/Input/ControllerManager.h"

#include "Marx/Input.h"
#include "Marx/Platform/Windows/WindowsWindow.h"

// Temporary
#include "Marx/Platform/D3D11/D3D11GraphicsContext.h"
#include "Marx/Platform/D3D11/D3D11InfoException.h"
#include "Marx/Platform/D3D11/D3D11ExceptionMacros.h"
#include "Marx/Platform/D3D11/D3D11InfoManager.h"

#include "Marx/Platform/D3D11/D3D11Shader.h"
#include "Marx/Renderer/Buffer.h"

namespace Marx
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		MX_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		m_pWindow.reset(Window::create());
		m_pWindow->setEventCallback(MX_BIND_EVENT_METHOD(Application::onEvent));

		m_pImGuiLayer = new ImGuiLayer;
		pushOverlay(m_pImGuiLayer);

		ControllerManager::init(MX_BIND_EVENT_METHOD(Application::onEvent));

		// Vertex Buffer
		float vertices[3 * 5] =
		{
			-0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.0f,  0.5f, 0.4f, 0.8f, 0.4f,
			 0.5f, -0.5f, 0.2f, 0.2f, 0.8f,
		};
		m_pVertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		m_pIndexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Shader
		m_pShader = std::make_unique<D3D11Shader>(
			Shader::loadShaderSrcFromFile("C:\\dev\\Marx\\Marx\\src\\shaders\\vertexShader.hlsl"),
			Shader::loadShaderSrcFromFile("C:\\dev\\Marx\\Marx\\src\\shaders\\pixelShader.hlsl")
		);
		// Vertex Layout
		m_pVertexBuffer->setLayout({
			{ ShaderDataType::Float2, "POSITION" },
			{ ShaderDataType::Float3, "COLOR" }
		});

		float sqVertices[4 * 5] =
		{
			-0.75f, -0.75f, 0.0f, 0.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			 0.75f, -0.75f, 1.0f, 0.0f, 0.0f,
		};
		m_pSqVertexBuffer.reset(VertexBuffer::create(sqVertices, sizeof(sqVertices)));
		uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		m_pSqIndexBuffer.reset(IndexBuffer::create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		m_pSqVertexBuffer->setLayout({
			{ ShaderDataType::Float2, "POSITION" },
			{ ShaderDataType::Float3, "COLOR" }
		});
	}

	Application::~Application()
	{
		ControllerManager::shutdown();
	}

	void Application::run()
	{
		while (m_running)
		{
			m_pWindow->clear(0.1f, 0.1f, 0.1f);

			// Temporary
			D3D11GraphicsContext::D3D11Manager::getContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_pShader->bind();

			m_pVertexBuffer->bind();
			m_pIndexBuffer->bind();
			D3D11GraphicsContext::D3D11Manager::getContext().DrawIndexed(m_pIndexBuffer->getCount(), 0, 0);

			m_pSqVertexBuffer->bind();
			m_pSqIndexBuffer->bind();
			D3D11GraphicsContext::D3D11Manager::getContext().DrawIndexed(m_pSqIndexBuffer->getCount(), 0, 0);

			for (Layer* layer : m_layerStack)
				layer->onUpdate();

			m_pImGuiLayer->begin();
			for (Layer* layer : m_layerStack)
				layer->onImGuiRender();
			m_pImGuiLayer->end();

			m_pWindow->onUpdate();

			ControllerManager::onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(MX_BIND_EVENT_METHOD(Application::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_layerStack.pushOverlay(overlay);
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		e.getWnd()->shutdown();
		if (Win32Window::getWndCount() == 0)
		{
			m_running = false;
		}
		return true;
	}
}