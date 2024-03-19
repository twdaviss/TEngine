#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void SolarSystem::Initialize()
{
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
}

void SolarSystem::Terminate()
{
}

void SolarSystem::Update(float deltaTime)
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
		currentShape = Shape::Transform;
	}
	if (input->IsKeyDown(KeyCode::TWO))
	{
		currentShape = Shape::Sphere;
	}
	if (input->IsKeyDown(KeyCode::THREE))
	{
		currentShape = Shape::Aabb;
	}
	if (input->IsKeyDown(KeyCode::FOUR))
	{
		currentShape = Shape::Aabbfilled;
	}
	if (input->IsKeyDown(KeyCode::FIVE))
	{
		currentShape = Shape::Lines;
	}
}

void SolarSystem::Render()
{
	/*SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::AddGroundPlane(20, Colors::White);
	SimpleDraw::AddSphere(60, 60, 1.0f, { 1.0f, 1.0f, 0.0f, 0.7f });*/

	switch (currentShape) 
	{
	case Shape::Transform:
		SimpleDraw::AddTransform(Matrix4::Identity);
		break;
	case Shape::Sphere:
		SimpleDraw::AddSphere(60, 60, 1.0f, { 1.0f, 1.0f, 0.0f, 0.7f });
		break;
	case Shape::Aabb:
		SimpleDraw::AddAABB({ 10,10,10 }, { 100,100,100 }, Colors::Red);
		break;
	case Shape::Aabbfilled:
		SimpleDraw::AddFilledAABB(10,10,10,100,100,100, Colors::Red);
		break;
	case Shape::Lines:
		SimpleDraw::AddLine({ 0,0,0},{0,2.5,0},Colors::Red);
		SimpleDraw::AddLine({ 2.5,0,0 }, { 2.5,2.5,0 }, Colors::Red);
		SimpleDraw::AddLine({ 0,1.25,0 }, { 2.5,1.25,0 }, Colors::Red);

		SimpleDraw::AddLine({ 5,0,0 }, { 5,2.5,0 }, Colors::Red);

		break;
	}
	SimpleDraw::Render(mCamera);
}
