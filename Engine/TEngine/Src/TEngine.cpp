#include "Precompiled.h"
#include "TEngine.h"

TEngine::App& TEngine::MainApp()
{
	static App sApp;
	return sApp;
}