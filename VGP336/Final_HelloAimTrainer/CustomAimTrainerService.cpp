#include "CustomAimTrainerService.h"
#include "CustomAimTrainerComponent.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;
using namespace TEngine::Physics;
using namespace TEngine::Input;

void CustomAimTrainerService::CustomInitialize()
{
	UIRenderService* renderService = GetWorld().GetService<UIRenderService>();
	renderService->Register(&mTextComponent);
	int index = 00;
	
	std::string name = "Target";
	mTarget = GetWorld().CreateGameObject(name);
	TransformComponent* tf = mTarget->AddComponent<TransformComponent>();
		
	MeshComponent* mb = mTarget->AddComponent<MeshComponent>();
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

	RigidBodyComponent* rb = mTarget->AddComponent<RigidBodyComponent>();
	CollisionShape* collisionShape = new CollisionShape();
	collisionShape->InitializeSphere(mRadius);
	rb->SetParameters(*collisionShape, 0.0);
	mTarget->Initialize();
	SpawnTarget();
}

void CustomAimTrainerService::Terminate()
{
	mAimTrainerComponent.Terminate();
}

void CustomAimTrainerService::Shoot()
{
	++mTotalShots;
	Vector3 position = GetWorld().GetService<CameraService>()->GetMain().GetPosition();
	Vector3 direction = GetWorld().GetService<CameraService>()->GetMain().GetDirection();
	Vector3 dest = position + Math::Normalize(direction) * 50;
	if (PhysicsWorld::Get()->PerformRayCast(ConvertTobtVector3(position), ConvertTobtVector3(dest)))
	{
		++mHits;
		SpawnTarget();
		mTotalTime += mCurrentLife;
		++mTotalTargets;
		mCurrentLife = 0;
	}
	else 
	{
		++mMisses;
	}
}

void CustomAimTrainerService::Update(float deltaTime)
{
	if (!initialized)
	{
		CustomInitialize();
		initialized = true;
	}
	
	mCurrentLife += deltaTime;
	if (mCurrentLife > mLifeTime)
	{
		SpawnTarget();
		mTotalTime += mLifeTime;
		mCurrentLife = 0.0;
		++mTotalTargets;
	}
	if (InputSystem::Get()->IsMousePressed(MouseButton::LBUTTON))
	{
		Shoot();
	}

	if (mTotalTargets > 0)
	{
		mAvgTime = mTotalTime/ mTotalTargets;
	}

	float accuracy = 0;
	if (mTotalShots > 0)
	{
		accuracy = (float)mHits / (float)mTotalShots * 100;
	}
	mTextComponent.SetText(
		"Hits: " + std::to_string(mHits) +
		"\nMisses: " + std::to_string(mMisses) +
		"\nAccuracy: " + std::to_string((int)accuracy) +
		"\nAverage Time: " + std::to_string(mAvgTime),
		{0,0}, 24, Colors::White);

	mTextComponent.Render();
	mAimTrainerComponent.Update(deltaTime);
}

void CustomAimTrainerService::SpawnTarget()
{
	float randX = rand() % 20;
	float randY = rand() % 20;
	RigidBodyComponent* rb = mTarget->GetComponent<RigidBodyComponent>();

	rb->SetPosition({randX,randY,10});
}

