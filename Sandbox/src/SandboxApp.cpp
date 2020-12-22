#include <Marx.h>

class ExampleLayer : public Marx::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void onUpdate() override
	{
		MX_INFO("ExampleLayer::onUpdate");
	}

	void onEvent(Marx::Event& event) override
	{
		MX_TRACE("{0}", event);
	}
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