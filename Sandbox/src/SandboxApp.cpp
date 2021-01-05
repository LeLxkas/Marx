#include <Marx.h>

#include "imgui/imgui.h"

#include <functional>

class ExampleLayer : public Marx::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		// Vertex Buffer
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
		};
		m_pVertexBuffer.reset(Marx::VertexBuffer::create(vertices, sizeof(vertices)));
		// Vertex Layout
		m_pVertexBuffer->setLayout({
			{ Marx::ShaderDataType::Float3, "POSITION" },
			{ Marx::ShaderDataType::Float3, "COLOR" }
			});

		// Index Buffer
		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		m_pIndexBuffer.reset(Marx::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t), Marx::IndexBuffer::PrimitiveType::TriangleList));

		// Shader
		m_pShader.reset(
			Marx::Shader::create(
				Marx::Shader::loadShaderSrcFromFile("C:\\dev\\Marx\\Marx\\src\\shaders\\vertexShader.hlsl"),
				Marx::Shader::loadShaderSrcFromFile("C:\\dev\\Marx\\Marx\\src\\shaders\\pixelShader.hlsl")
			)
		);

		// Vertex Array
		m_pVertexArray.reset(Marx::VertexArray::create());
		m_pVertexArray->setVertexBuffer(m_pVertexBuffer);
		m_pVertexArray->setIndexBuffer(m_pIndexBuffer);
	}

	void onUpdate(Marx::Timestep ts) override
	{
		static float rotation = 0.0f;
		rotation += 90.0f * ts;
		Marx::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Marx::RenderCommand::clear();

		m_camera.setPosition({ m_mouseX, m_mouseY, 0.0f });
		m_camera.setRotation(rotation);
		Marx::Renderer::beginScene(m_camera);
		Marx::Renderer::submit(m_pShader, m_pVertexArray);
		Marx::Renderer::endScene();
	}

	virtual void onImGuiRender() override
	{}

	void onEvent(Marx::Event& event) override
	{
		Marx::EventDispatcher dispatcher(event);
		dispatcher.dispatch<Marx::MouseMoveEvent>(MX_BIND_EVENT_METHOD(ExampleLayer::onMouseMove));
		dispatcher.dispatch<Marx::MouseButtonPressEvent>(MX_BIND_EVENT_METHOD(ExampleLayer::onMouseButtonPress));
	}

	bool onMouseMove(Marx::MouseMoveEvent& e)
	{
		m_mouseX = -(e.getX() / (Marx::Application::get()->getWindow()->getWidth() / 2) - 1.0f) * 1.6f;
		m_mouseY = e.getY() / (Marx::Application::get()->getWindow()->getHeight() / 2) - 1.0f;
		return true;
	}

	bool onMouseButtonPress(Marx::MouseButtonPressEvent& e)
	{
		MX_TRACE("MouseButtonPress: {0}", e.getButton());
		return true;
	}
private:
	std::shared_ptr<Marx::IndexBuffer> m_pIndexBuffer;
	std::shared_ptr<Marx::Shader> m_pShader;
	std::shared_ptr<Marx::VertexBuffer> m_pVertexBuffer;
	std::shared_ptr<Marx::VertexArray> m_pVertexArray;
	Marx::OrthographicCamera m_camera;
	float m_mouseX = 0.0f;
	float m_mouseY = 0.0f;
};

class Sandbox : public Marx::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}
	~Sandbox()
	{}
};

Marx::Application* Marx::createApplication()
{
	return new Sandbox();
}