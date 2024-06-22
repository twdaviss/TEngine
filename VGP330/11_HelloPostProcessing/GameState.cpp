#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	Model ninjaModel;
	Model vampireModel;
	ModelIO::LoadModel("../../Assets/Models/Ninja/Ch24_nonPBR.fbx", ninjaModel);
	ModelIO::LoadMaterial("../../Assets/Models/Ninja/Ch24_nonPBR.fbx", ninjaModel);

	ModelIO::LoadModel("../../Assets/Models/Vampire/vampire.fbx", vampireModel);
	ModelIO::LoadMaterial("../../Assets/Models/Vampire/vampire.fbx", vampireModel);

	mCharacter = CreateRenderGroup(ninjaModel);
	mCharacter2 = CreateRenderGroup(vampireModel);

	Mesh groundMesh = MeshBuilder::CreateHorizontalPlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	MeshPX screenQuad = MeshBuilder::CreateScreenQuad();
	mScreenQuad.meshBuffer.Initialize(screenQuad);

	SetRenderGroupPosition(mCharacter, { -1,0,0 });
	SetRenderGroupPosition(mCharacter2, { 1,0,0 });

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	shaderFilePath = L"../../Assets/Shaders/PostProcessing.fx";
	mPostProcessingEffect.Initialize(shaderFilePath);
	mPostProcessingEffect.SetTexture(&mRenderTarget);
	mPostProcessingEffect.SetTexture(&mCombineTexture, 1);

	GraphicsSystem* gs = GraphicsSystem::Get();
	const uint32_t screenWidth = gs->GetBackBufferWidth();
	const uint32_t screenHeight = gs->GetBackBufferHeight();

	mRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	mCombineTexture.Initialize("../../Assets/Images/water/water_spec.jpg");
}

void GameState::Terminate()
{
	mCombineTexture.Terminate();
	mRenderTarget.Terminate();
	mPostProcessingEffect.Terminate();
	mStandardEffect.Terminate();
	mScreenQuad.Terminate();
	mGround.Terminate();
	CleanupRenderGroup(mCharacter);
	CleanupRenderGroup(mCharacter2);
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
	/*SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);*/

	mRenderTarget.BeginRender();
		mStandardEffect.Begin();
			DrawRenderGroup(mStandardEffect, mCharacter);
			DrawRenderGroup(mStandardEffect, mCharacter2);
			mStandardEffect.Render(mGround);
		mStandardEffect.End();
	mRenderTarget.EndRender();

	mPostProcessingEffect.Begin();
		mPostProcessingEffect.Render(mScreenQuad);
	mPostProcessingEffect.End();
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

	ImGui::Separator();
	ImGui::Text("Render Target:");
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 128,128 },
		{ 0,0 },
		{ 1,1 },
		{ 1,1,1,1 },
		{ 1,1,1,1 }
	);

	mStandardEffect.DebugUI();
	mPostProcessingEffect.DebugUI();
	ImGui::End();
}