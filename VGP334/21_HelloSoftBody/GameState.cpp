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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 1.0f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");
	mBall.transform.position = { 0.0f, 5.0f, 0.0f };
	mBallShape.InitializeSphere(1.0f);
	mBallRB.Initialize(mBall.transform, mBallShape, 10.0f);

	Mesh ground = MeshBuilder::CreateHorizontalPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");
	mGroundShape.InitializeHull({ 5.0f,0.5f,5.0f }, { 0.05f, -0.5f,0.0f });
	mGroundRB.Initialize(mGround.transform, mGroundShape);

	int rows = 10;
	int cols = 10;
	mClothMesh = MeshBuilder::CreateHorizontalPlane(rows, cols, 1.0f);
	for (Vertex& v : mClothMesh.vertices)
	{
		v.position.y = 10.0f;
	}
	uint32_t lastVertex = mClothMesh.vertices.size() - 1;
	uint32_t lastVertexOtherSide = lastVertex - rows;
	mClothSoftBody.Initialize(mClothMesh, 1.0f, { lastVertex, lastVertexOtherSide });
	mCloth.meshBuffer.Initialize(nullptr, sizeof(Vertex), mClothMesh.vertices.size(),
		mClothMesh.indices.data(), mClothMesh.indices.size());
	mCloth.diffuseMapId = TextureManager::Get()->LoadTexture("planets/earth/earth.jpg");
}

void GameState::Terminate()
{
	mCloth.Terminate();
	mClothSoftBody.Terminate();
	mGroundRB.Terminate();
	mGroundShape.Terminate();
	mGround.Terminate();
	mBallRB.Terminate();
	mBallShape.Terminate();
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

	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		mBallRB.SetPosition({ 0.0f, 10.0f, 0.0f });
		mBallRB.SetVelocity({ 0.0f, 0.0f, 0.0f });
	}

	if (input->IsMousePressed(MouseButton::LBUTTON))
	{
		mBallRB.SetPosition(mCamera.GetPosition());
		mBallRB.SetVelocity(mCamera.GetDirection() * 50.0f);
	}
}

void GameState::Render()
{
	mCloth.meshBuffer.Update(mClothMesh.vertices.data(), mClothMesh.vertices.size());
	mStandardEffect.Begin();
		mStandardEffect.Render(mBall);
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mCloth);
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
		Physics::PhysicsWorld::Get()->DebugUI();
	ImGui::End();

	SimpleDraw::Render(mCamera);
}