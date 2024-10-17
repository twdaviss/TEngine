#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Audio;

void GameState::Initialize()
{
	//add components first
	mGameObject.AddComponent<TransformComponent>();
	//and then initialize
	mGameObject.Initialize();

	mCameraGameObject.AddComponent<CameraComponent>();
	mCameraGameObject.AddComponent<FPSCameraComponent>();
	mCameraGameObject.Initialize();
}

void GameState::Terminate()
{
	mCameraGameObject.Terminate();
	mGameObject.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameObject.Update(deltaTime);
	mCameraGameObject.Update(deltaTime);
}

void GameState::Render()
{
	//TODO
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameObject.DebugUI();
		mCameraGameObject.DebugUI();
	ImGui::End();

	const CameraComponent* cameraComponent = mCameraGameObject.GetComponent<CameraComponent>();
	SimpleDraw::Render(cameraComponent->GetCamera());
}