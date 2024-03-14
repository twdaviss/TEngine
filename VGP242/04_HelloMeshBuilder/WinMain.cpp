#include <TEngine/Inc/TEngine.h>

#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& myApp = TEngine::MainApp();
	myApp.AddState<SkyBoxState>("SkyBoxState");
	myApp.AddState<RectangleState>("RectangleState");
	myApp.AddState<CubeState>("CubeState");
	myApp.AddState<SphereState>("SphereState");
	myApp.AddState<CylinderState>("CylinderState");
	myApp.AddState<HorizontalPlaneState>("HorizontalPlaneState");
	myApp.AddState<SkySphereState>("SkySphereState");


	AppConfig config;
	config.appName = L"Hello Shape";
	myApp.Run(config);

	myApp.Quit();
	return(0);
}