#include "Precompiled.h"
#include "FPSCameraComponent.h"

#include "GameObject.h"
#include "CameraComponent.h"
#include "SaveUtil.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void FPSCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Camera not found");
}

void FPSCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}

void FPSCameraComponent::Update(float deltaTime)
{
	Camera& camera = mCameraComponent->GetCamera();

	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		camera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}

void FPSCameraComponent::Seriliaze(rapidjson::Document& doc, rapidjson::Value& value)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::SaveFloat("MoveSpeed", mMoveSpeed, doc, componentValue);
	SaveUtil::SaveFloat("ShiftSpeed", mShiftSpeed, doc, componentValue);
	SaveUtil::SaveFloat("TurnSpeed", mTurnSpeed, doc, componentValue);
	value.AddMember("FPSCameraComponent", componentValue, doc.GetAllocator());
}

void FPSCameraComponent::Deseriliaze(const rapidjson::Value& value)
{
	if (value.HasMember("MoveSpeed"))
	{
		mMoveSpeed = value["MoveSpeed"].GetFloat();
	}
	if (value.HasMember("ShiftSpeed"))
	{
		mMoveSpeed = value["ShiftSpeed"].GetFloat();
	}
	if (value.HasMember("TurnSpeed"))
	{
		mMoveSpeed = value["TurnSpeed"].GetFloat();
	}
}
