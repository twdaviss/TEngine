#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	//create a shape
	TextureManager* tm = TextureManager::Get();
	mMesh = MeshBuilder::CreateSphere(100, 100, 1.0f);
	mRenderObject.meshBuffer.Initialize(mMesh);
	mRenderObject.diffuseTextureId = tm->LoadTexture("planets/earth/earth.jpg");

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mRenderObject.Terminate();
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
	if (input->IsKeyDown(KeyCode::ONE))
	{
		MainApp().ChangeState("RectangleState");
	}
	if (input->IsKeyDown(KeyCode::TWO))
	{
		MainApp().ChangeState("CubeState");
	}
	if (input->IsKeyDown(KeyCode::THREE))
	{
		MainApp().ChangeState("CylinderState");
	}
	if (input->IsKeyDown(KeyCode::FOUR))
	{
		MainApp().ChangeState("SphereState");
	}
	if (input->IsKeyDown(KeyCode::FIVE))
	{
		MainApp().ChangeState("HorizontalPlaneState");
	}
	if (input->IsKeyDown(KeyCode::SIX))
	{
		MainApp().ChangeState("SkyBoxState");
	}
	if (input->IsKeyDown(KeyCode::SEVEN))
	{
		MainApp().ChangeState("SkySphereState");
	}
}

void GameState::Render()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	mStandardEffect.Begin();
		mStandardEffect.Render(mRenderObject);
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mStandardEffect.DebugUI();
	ImGui::End();
}