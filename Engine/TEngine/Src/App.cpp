#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace TEngine;
using namespace TEngine::Core;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Graphics::SimpleDraw;

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
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);
	InputSystem::StaticInitialize(handle);
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize(config.maxVertexCount);

	ASSERT(mCurrentState != nullptr, "App: need an app state");
	mCurrentState->Initialize();

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		InputSystem* input = InputSystem::Get();
		input->Update();

		if (!myWindow.isActive() || input->IsKeyPressed(KeyCode::ESCAPE)) {
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
		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
			mCurrentState->Render();
			DebugUI::BeginRender();
				mCurrentState->DebugUI();
			DebugUI::EndRender();
		gs->EndRender();
	}

	mCurrentState->Terminate();

	SimpleDraw::StaticTerminate();
	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}
void App::Quit()
{
	mRunning = false;
}