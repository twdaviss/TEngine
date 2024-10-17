#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Audio;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.Initialize();

	GameObject* gameObject = mGameWorld.CreateGameObject("Object0");
	//add components first
	gameObject->AddComponent<TransformComponent>();
	//and then initialize
	gameObject->Initialize();

	GameObject* cameraGameObject = mGameWorld.CreateGameObject("Camera");

	cameraGameObject->AddComponent<CameraComponent>();
	cameraGameObject->AddComponent<FPSCameraComponent>();
	cameraGameObject->Initialize();
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameWorld.DebugUI();
	ImGui::End();
}