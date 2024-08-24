#pragma once

#include <TEngine/Inc/TEngine.h>

class GameState : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	TEngine::Graphics::DirectionalLight mDirectionalLight;
	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::StandardEffect mStandardEffect;

	TEngine::Graphics::RenderObject mBall;
	TEngine::Physics::CollisionShape mBallShape;
	TEngine::Physics::RigidBody mBallRB;

	TEngine::Graphics::RenderObject mGround;
	TEngine::Physics::CollisionShape mGroundShape;
	TEngine::Physics::RigidBody mGroundRB;

	TEngine::Graphics::RenderObject mCloth;
	TEngine::Graphics::Mesh mClothMesh;
	TEngine::Physics::SoftBody mClothSoftBody;
};

