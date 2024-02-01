#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace TEngine;
using namespace TEngine::Core;

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end()) 
	{
		mNextState = iter->second.get();
	}
}

void App::Run(const AppConfig& config)
{
	LOG("App Started: %.3f", TimeUtil::GetTime());

	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	ASSERT(myWindow.isActive(), "Failed to create a window");

	ASSERT(mCurrentState != nullptr, "App: need an app state");
	mCurrentState->Initialize();

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();

		if (!myWindow.isActive()) {
			Quit();
			break;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}
		float deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);
	}
	mCurrentState->Terminate();
	myWindow.Terminate();
}
void App::Quit()
{
	mRunning = false;
}