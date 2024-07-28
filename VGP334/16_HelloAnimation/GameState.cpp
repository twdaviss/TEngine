#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,5.0f,-10.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateHorizontalPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	mAnimationTime = 0.0f;

	mAnimation = AnimationBuilder()
		//bounce 1
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 0.0f)
		.AddPositionKey({ 1.25f, 2.5, 0.0f }, 0.5f)
		.AddPositionKey({ 2.5f, 5.0, 0.0f },  1.0f)
		.AddPositionKey({ 3.75f, 2.5, 0.0f }, 1.5f)
		.AddPositionKey({ 5.0f, 0.0f, 0.0f }, 2.0f)

		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.0f)
		.AddScaleKey({ 0.9f, 1.8f, 0.9f }, 0.25f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 1.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 1.6f)
		.AddScaleKey({ 1.3f, 0.5f, 1.3f }, 1.9f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 2.0f)

		//bounce 2
		.AddPositionKey({ 3.75f, 2.5f, 0.0f }, 2.5f)
		.AddPositionKey({ 2.5f, 5.0f, 0.0f },  3.0f)
		.AddPositionKey({ 1.25f, 2.5f, 0.0f }, 3.5f)
		.AddPositionKey({ 0.0f, 0.0f, 0.0f },  4.0f)

		.AddScaleKey({ 0.9f, 1.8f, 0.9f }, 2.25f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 3.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 3.6f)
		.AddScaleKey({ 1.3f, 0.5f, 1.3f }, 3.9f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 4.0f)

		//bounce 3
		.AddPositionKey({ -1.25f, 2.5, 0.0f }, 4.5f)
		.AddPositionKey({ -2.5f, 5.0, 0.0f },  5.0f)
		.AddPositionKey({ -3.75f, 2.5, 0.0f }, 5.5f)
		.AddPositionKey({ -5.0f, 0.0f, 0.0f }, 6.0f)

		.AddScaleKey({ 0.9f, 1.8f, 0.9f }, 4.25f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 5.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 5.6f)
		.AddScaleKey({ 1.3f, 0.5f, 1.3f }, 5.9f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 6.0f)

		//bounce 4
		.AddPositionKey({ -3.75f, 2.5f, 0.0f }, 6.5f)
		.AddPositionKey({ -2.5f, 5.0f, 0.0f },  7.0f)
		.AddPositionKey({ -1.25f, 2.5f, 0.0f }, 7.5f)
		.AddPositionKey({ 0.0f, 0.0f, 0.0f },   8.0f)

		.AddScaleKey({ 0.9f, 1.8f, 0.9f }, 6.25f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 7.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 7.6f)
		.AddScaleKey({ 1.3f, 0.5f, 1.3f }, 7.9f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 8.0f)
		.Build();
}

void GameState::Terminate()
{
	mGround.Terminate();
	mBall.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	//update animation

	mAnimationTime += deltaTime;
	while (mAnimationTime > mAnimation.GetDuration())
	{
		mAnimationTime -= mAnimation.GetDuration();
	}
}

void GameState::Render()
{
	mBall.transform = mAnimation.GetTransform(mAnimationTime);

	mStandardEffect.Begin();
		mStandardEffect.Render(mBall);
		mStandardEffect.Render(mGround);
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
			{
				mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
			}
			ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
			ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
			ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
		}
		
		mStandardEffect.DebugUI();
	ImGui::End();
}