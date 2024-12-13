#include "CustomAimTrainerService.h"
#include "CustomAimTrainerComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;
using namespace TEngine::Physics;

void CustomAimTrainerService::Initialize()
{
	UIRenderService* renderService = GetWorld().GetService<UIRenderService>();
	renderService->Register(&mTextComponent);
	mAimTrainerComponent.Initialize();
}

void CustomAimTrainerService::Terminate()
{
	mAimTrainerComponent.Terminate();
}

void CustomAimTrainerService::Shoot()
{
	//PhysicsWorld::Get()->PerformRayCast();
}

void CustomAimTrainerService::Render()
{
	/*std::wstring text(L"Accuracy:");
	UIFont::Get()->DrawString(text.c_str(), {200,200}, 24, {1.0,1.0,1.0,1.0});*/
	//mAimTrainerComponent.Up
}

void CustomAimTrainerService::Update(float deltaTime)
{
	mTextComponent.SetText("Accuracy:", { 0,0 }, 24, Colors::White);
	mTextComponent.Render();
	mAimTrainerComponent.Update(deltaTime);
}

