#include "Precompiled.h"
#include "StationaryCameraComponent.h"

#include "GameObject.h"
#include "CameraComponent.h"
#include "SaveUtil.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void StationaryCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Camera not found");
}

void StationaryCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}

void StationaryCameraComponent::Update(float deltaTime)
{
	Camera& camera = mCameraComponent->GetCamera();

	auto input = Input::InputSystem::Get();
	const float turnSpeed = 0.1f;
	int moveX = input->GetMouseMoveX();
	int moveY = input->GetMouseMoveY();
	if (InputSystem::Get()->IsKeyPressed(KeyCode::TAB))
	{
		InputSystem::Get()->ToggleMouseLockPosition();
	}
	camera.Yaw(moveX * turnSpeed * deltaTime );
	camera.Pitch(moveY * turnSpeed * deltaTime);
}

void StationaryCameraComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::SaveFloat("TurnSpeed", mTurnSpeed, doc, componentValue);
	value.AddMember("FPSCameraComponent", componentValue, doc.GetAllocator());
}

void StationaryCameraComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("TurnSpeed"))
	{
		mTurnSpeed = value["TurnSpeed"].GetFloat();
	}
}
