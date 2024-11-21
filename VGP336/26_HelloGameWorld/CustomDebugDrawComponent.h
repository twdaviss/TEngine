#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public TEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw();

private:
	const TEngine::TransformComponent* mTransformComponent = nullptr;
	TEngine::Math::Vector3 mPosition = TEngine::Math::Vector3::Zero;
	TEngine::Color mColor = TEngine::Colors::White;
	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;

};

