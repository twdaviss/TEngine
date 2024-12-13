#include "CustomAimTrainerService.h"
#include "CustomAimTrainerComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;
using namespace TEngine::Physics;

void CustomAimTrainerService::CustomInitialize()
{
	UIRenderService* renderService = GetWorld().GetService<UIRenderService>();
	renderService->Register(&mTextComponent);

	for (GameObject* target : mTargets)
	{
		target = GetWorld().CreateGameObject("Target");
		TransformComponent* tf = target->AddComponent<TransformComponent>();
		RigidBodyComponent* rb = target->AddComponent<RigidBodyComponent>();
		CollisionShape* collisionShape = new CollisionShape();
		collisionShape->InitializeSphere(mRadius);

		rb->SetParameters(*collisionShape, 0);
		rb->Initialize();
		rb->SetPosition({ 10, 10, 10 });
	}
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
	if (!initialized)
	{
		CustomInitialize();
		initialized = true;
	}
	mTextComponent.SetText("Accuracy:", { 0,0 }, 24, Colors::White);
	mTextComponent.Render();
	mAimTrainerComponent.Update(deltaTime);
}

void CustomAimTrainerService::SpawnTarget()
{

}

