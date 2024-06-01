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
	//mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	mTerrain.Initialize("../../Assets/Images/terrain/heightmap_512x512.raw", 20.0f);
	const Mesh& m = mTerrain.GetMesh();
	mGround.meshBuffer.Initialize(
		nullptr,
		static_cast<uint32_t>(sizeof(Vertex)),
		static_cast<uint32_t>(m.vertices.size()),
		m.indices.data(),
		static_cast<uint32_t>(m.indices.size())
	);
	mGround.meshBuffer.Update(m.vertices.data(), m.vertices.size());
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("terrain/grass_2048.jpg");
	mGround.bumpMapId = TextureManager::Get()->LoadTexture("terrain/dirt_seamless.jpg");

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());

	mTerrainEffect.Initialize();
	mTerrainEffect.SetCamera(mCamera);
	mTerrainEffect.SetDirectionalLight(mDirectionalLight);
	mTerrainEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mTerrainEffect.SetShadowMap(mShadowEffect.GetDepthMap());

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	
}

void GameState::Terminate()
{
	mShadowEffect.Terminate();
	mTerrainEffect.Terminate();
	mStandardEffect.Terminate();
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

	if (mOnTerrain)
	{
		Vector3 pos = mCamera.GetPosition();
		float height = mTerrain.GetHeight(pos);
		pos.y = height + 3.0f;
		mCamera.SetPosition(pos);
		
		height = mTerrain.GetHeight({ 10.0, 0.0f, 10.0f });
		SetRenderGroupPosition(mCharacter, { 10,height,10 });
		height = mTerrain.GetHeight({ 15.0f, 0.0f, 20.0f });
		SetRenderGroupPosition(mCharacter2, { 15.0f,height,20.0f });
	}
}

void GameState::Render()
{
	/*SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);*/

	mShadowEffect.SetFocus(mCamera.GetPosition());

	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mCharacter);
		DrawRenderGroup(mShadowEffect, mCharacter2);
		mShadowEffect.Render(mGround);
	mShadowEffect.End();

	mTerrainEffect.Begin();
		mTerrainEffect.Render(mGround);
	mTerrainEffect.End();

	mStandardEffect.Begin();
		DrawRenderGroup(mStandardEffect, mCharacter);
		DrawRenderGroup(mStandardEffect, mCharacter2);
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

		if (ImGui::CollapsingHeader("Terrain", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Checkbox("OnTerrain", &mOnTerrain);
			float heightScale = mTerrain.GetHeightScale();
			if (ImGui::DragFloat("HeightScale", &heightScale, 0.1f, 1.0f, 100.0f))
			{
				mTerrain.SetHeightScale(heightScale);
				const Mesh& m = mTerrain.GetMesh();
				mGround.meshBuffer.Update(m.vertices.data(), m.vertices.size());
			}
		}
		mStandardEffect.DebugUI();
		mTerrainEffect.DebugUI();
		mShadowEffect.DebugUI();
	ImGui::End();
}