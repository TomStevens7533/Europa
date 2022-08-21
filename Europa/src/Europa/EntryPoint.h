#pragma once

#ifdef EU_PLATFORM_WINDOWS
#ifdef EU_DEBUG
#include "VLD/include/vld.h"
#endif

extern	Eu::Application* Eu::CreateApplication();

int main(int argc, char** argv)
{
	Eu::Log::Init();
	EU_CORE_WARN("Initialized CoreLog!");


	auto app = Eu::CreateApplication();
	app->Run();
	delete app;
}

#endif // EU_PLATFORM_WINDOWS

