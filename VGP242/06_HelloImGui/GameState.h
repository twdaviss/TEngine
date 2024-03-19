#pragma once

#include <TEngine/Inc/TEngine.h>

class SolarSystem : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	TEngine::Graphics::Camera mCamera;
	float mObjectAlpha = 1.0f;
	Math::Vector3 mTransformPosition = Math::Vector3::Zero;
};
