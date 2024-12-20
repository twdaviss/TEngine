#include "CustomDebugDrawComponent.h"
#include "CustomDebugDrawService.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;

void CustomDebugDrawComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	CustomDebugDrawService* drawServices = GetOwner().GetWorld().GetService<CustomDebugDrawService>();
	drawServices->Register(this);
}

void CustomDebugDrawComponent::Terminate()
{
	CustomDebugDrawService* drawServices = GetOwner().GetWorld().GetService<CustomDebugDrawService>();
	drawServices->Unregister(this);
}

void CustomDebugDrawComponent::Update(float deltaTime)
{
}

void CustomDebugDrawComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Slices"))
	{
		mSlices = static_cast<uint32_t>(value["Slices"].GetInt());
	}
	if (value.HasMember("Rings"))
	{
		mRings = static_cast<uint32_t>(value["Rings"].GetInt());
	}
	if (value.HasMember("Radius"))
	{
		mRadius = static_cast<uint32_t>(value["Radius"].GetFloat());
	}
	if (value.HasMember("Position"))
	{
		auto position = value["Position"].GetArray();
		mPosition.x = position[0].GetFloat();
		mPosition.y = position[1].GetFloat();
		mPosition.z = position[2].GetFloat();
	}
	if (value.HasMember("Color"))
	{
		auto position = value["Color"].GetArray();
		mColor.r = position[0].GetFloat();
		mColor.g = position[1].GetFloat();
		mColor.b = position[2].GetFloat();
		mColor.a = position[3].GetFloat();
	}
}

void CustomDebugDrawComponent::AddDebugDraw()
{
	Vector3 worldSpace = mPosition;
	if (mTransformComponent != nullptr)
	{
		Matrix4 matWorld = mTransformComponent->GetMatrix4();
		worldSpace = TransformCoord(mPosition, matWorld);
	}
	SimpleDraw::AddSphere(mSlices, mRings, mRadius, worldSpace, mColor);
}
