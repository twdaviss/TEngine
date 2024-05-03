#include <TEngine/Inc/TEngine.h>

#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = TEngine::MainApp();
	myApp.AddState<GameState>("GameState");

	AppConfig config;
	config.appName = L"Hello Render Target";
	myApp.Run(config);

	myApp.Quit();
	return(0);
}