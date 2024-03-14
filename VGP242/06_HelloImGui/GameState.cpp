#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

const char* shapeType[] =
{
	"Sphere",
	"AABB",
	"Circle"
};
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
Color shapeColor = Colors::White;
bool checkOn = false;
int currentValue = 1;
void GameState::DebugUI()
{
	DebugUI::SetTheme(DebugUI::Theme::Dark);
	ImGui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::LabelText("","Draw Simple Shapes");
	
	if (ImGui::CollapsingHeader("Shape Specifications", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("SphereAlpha", &mObjectAlpha, 0.01f, 0.0f, 1.0f);
		shapeColor.a = mObjectAlpha;

		ImGui::DragFloat3("TransformPos", &mTransformPosition.x, 0.01f, -2.0f, 2.0f);

		ImGui::ColorEdit4("Object Color", &shapeColor.r);
		mObjectAlpha = shapeColor.a;
	}
	if (ImGui::Combo("ShapeType", &currentValue, shapeType, 3))
	{
		//do stuff
	}
	if (ImGui::Checkbox("Enable Debug", &checkOn))
	{
		//do stuff

	}
	ImGui::End();

	if (checkOn)
	{
		SimpleDraw::AddTransform(Matrix4::Identity);
		SimpleDraw::AddTransform(Matrix4::Translation(mTransformPosition));
		SimpleDraw::AddGroundPlane(20, Colors::White);
	}

	switch (currentValue)
	{
	case 0: SimpleDraw::AddSphere(60, 60, 1.0f, shapeColor); break;
	case 1: SimpleDraw::AddAABB(-Math::Vector3::One, Math::Vector3::One, shapeColor); break;
	case 2: SimpleDraw::AddGroundCircle(60, 1.0f, shapeColor); break;
	default:
		break;
	}

	
	
	//SimpleDraw::AddSphere(60, 60, 1.0f, { 1.0f, 1.0f, 0.0f, mSphereAlpha });
	SimpleDraw::Render(mCamera);
}
