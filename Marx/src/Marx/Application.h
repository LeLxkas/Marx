#pragma once

#include "Core.h"

namespace Marx {

	class MARX_API Application {
	public:
		Application();
		~Application();
	public:
		void run();
	};

	// To be defined by client
	Application* createApplication();
}