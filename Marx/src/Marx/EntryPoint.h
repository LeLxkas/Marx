#pragma once

#include "Marx/Exceptions/MarxException.h"

#ifdef MX_PLATFORM_WINDOWS

extern Marx::Application* Marx::createApplication();

#define MX_EXCEPT_LOG(except) MX_CRITICAL(except.what())
#define MX_STD_EXCEPT_LOG(except) MX_CRITICAL(except.what())

#define MX_EXCEPT_BOX(except) MessageBox(NULL, except.what(), except.getName(), MB_ICONEXCLAMATION | MB_OK)
#define MX_STD_EXCEPT_BOX(except) MessageBox(NULL, except.what(), "std::exception", MB_ICONEXCLAMATION | MB_OK)

int main(int argc, char** argv)
{
	Marx::Log::init();
	MX_CORE_INFO("Initialized Log!");

	Marx::Application* app;

	try
	{
		app = Marx::createApplication();
		app->run();
		delete app;
	}
	catch (const Marx::MarxException& except)     { MX_EXCEPT_LOG(except);     MX_EXCEPT_BOX(except); }
	catch (const std::exception& except)          { MX_STD_EXCEPT_LOG(except); MX_STD_EXCEPT_BOX(except); }
}

#undef MX_EXCEPT_BOX
#undef MX_STD_EXCEPT_BOX

#endif