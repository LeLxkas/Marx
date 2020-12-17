#pragma once

#ifdef MX_PLATFORM_WINDOWS

extern Marx::Application* Marx::createApplication();

int main(int argc, char** argv) {
	auto app = Marx::createApplication();
	app->run();
	delete app;
}
#endif