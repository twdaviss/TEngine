#include "GameState.h"

#include "CustomAimTrainerComponent.h"
#include "CustomAimTrainerService.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;
using namespace TEngine::Audio;

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomAimTrainerComponent")
	{
		return gameObject.AddComponent<CustomAimTrainerComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomAimTrainerComponent")
	{
		return gameObject.AddComponent<CustomAimTrainerComponent>();
	}
	return nullptr;
}

Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
{
	if (serviceName == "CustomAimTrainerService")
	{
		return gameWorld.AddService<CustomAimTrainerService>();
	}
	return nullptr;
}

void GameState::Initialize()
{
	InputSystem::Get()->SetMouseLockPosition(true);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);
	GameWorld::SetCustomService(CustomServiceMake);

	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/aim_trainer_level.json");
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