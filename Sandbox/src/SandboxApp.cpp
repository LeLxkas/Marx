#include <Marx.h>

class Sandbox : public Marx::Application {
public:
	Sandbox() {
		;
	}

	~Sandbox() {
		;
	}
};

Marx::Application* Marx::createApplication() {
	return new Sandbox();
}