#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });
}

void GameState::Terminate()
{
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
}

void GameState::Render()
{
	
}
bool buttonOn = false;
void GameState::DebugUI()
{
	ImGui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::LabelText("Title", "Hello World");
	if (ImGui::Button("Button"))
	{
		buttonOn = !buttonOn;
	}
	if (buttonOn)
	{
		ImGui::LabelText("ButtonOn", "ItWasPressed");
	}
	ImGui::DragFloat("SphereAlpha", &mSphereAlpha, 0.01f, 0.0f, 1.0f);
	ImGui::End();

	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::AddGroundPlane(20, Colors::White);
	SimpleDraw::AddSphere(60, 60, 1.0f, { 1.0f, 1.0f, 0.0f, mSphereAlpha });
	SimpleDraw::Render(mCamera);
}
