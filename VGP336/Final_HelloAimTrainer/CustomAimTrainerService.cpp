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
	int index = 00;
	for (GameObject* target : mTargets)
	{
		++index;
		std::string name = "Target##" + std::to_string(index);
		target = GetWorld().CreateGameObject(name);
		TransformComponent* tf = target->AddComponent<TransformComponent>();
		RigidBodyComponent* rb = target->AddComponent<RigidBodyComponent>();
		MeshComponent* mb = target->AddComponent<MeshComponent>();

		Model::MeshData meshData;
		meshData.mesh = MeshBuilder::CreateSphere(mSlices, mRings, mRadius);
		Model::MaterialData matData;
		matData.diffuseMapName = "../../Assets/Images/Images/blue.jpg";
		matData.material.ambient = { 0.5, 0.5, 0.5, 1.0 };
		matData.material.diffuse = { 0.8, 0.8, 0.8, 1.0 };
		matData.material.specular = { 1.0, 1.0, 1.0, 1.0 };
		matData.material.emissive = { 0.0, 0.0, 0.0, 1.0 };
		matData.material.power = 10.0;

		mb->SetModelMesh(meshData, matData);

		CollisionShape* collisionShape = new CollisionShape();
		collisionShape->InitializeSphere(mRadius);

		RenderService* rs = GetWorld().GetService<RenderService>();
		int randX = rand() % 10;
		int randY = rand() % 10;

		rs->Register(mb);
		rb->SetParameters(*collisionShape, 0);
		rb->Initialize();
		rb->SetPosition({ (float)randX, (float)randY, 10 });
		target->Initialize();
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

