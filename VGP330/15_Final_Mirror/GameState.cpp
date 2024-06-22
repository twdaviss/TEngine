#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 10.0f,1.0f,5.0f });
	mCamera.SetLookAt({ 10.0f,1.0f,15.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, -1.0f });
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

	Mesh groundMesh = MeshBuilder::CreateHorizontalPlane(5, 5, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);

	mTerrain.Initialize("../../Assets/Images/terrain/heightmap_512x512.raw", 35.0f);
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

	Mesh mirrorMesh = MeshBuilder::CreateVerticalPlane(5, 5, 1.0f);
	mMirror.meshBuffer.Initialize(mirrorMesh);
	mMirror.diffuseMapId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");
	mMirror.specMapId = TextureManager::Get()->LoadTexture("terrain/blank_spec.jpg");

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());

	MeshPX screenQuad = MeshBuilder::CreateScreenQuad();
	mScreenQuad.meshBuffer.Initialize(screenQuad);

	shaderFilePath = L"../../Assets/Shaders/PostProcessing.fx";
	mPostProcessingEffect.Initialize(shaderFilePath);
	mPostProcessingEffect.SetTexture(&mPostProcessRenderTarget);
	mPostProcessingEffect.SetTexture(&mCombineTexture, 1);

	mTerrainEffect.Initialize();
	mTerrainEffect.SetCamera(mCamera);
	mTerrainEffect.SetDirectionalLight(mDirectionalLight);
	mTerrainEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mTerrainEffect.SetShadowMap(mShadowEffect.GetDepthMap());

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	GraphicsSystem* gs = GraphicsSystem::Get();
	const uint32_t screenWidth = gs->GetBackBufferWidth();
	const uint32_t screenHeight = gs->GetBackBufferHeight();

	mPostProcessRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	constexpr uint32_t size = 4096;
	mMirrorRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);

	mCombineTexture.Initialize("../../Assets/Images/water/water_spec.jpg");
}

void GameState::Terminate()
{
	mCombineTexture.Terminate();
	mMirrorRenderTarget.Terminate();
	mPostProcessRenderTarget.Terminate();
	mShadowEffect.Terminate();
	mTerrainEffect.Terminate();
	mScreenQuad.Terminate();
	mPostProcessingEffect.Terminate();
	mStandardEffect.Terminate();
	mMirror.Terminate();
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
		pos.y = height + 1.5f;
		mCamera.SetPosition(pos);
		
		height = mTerrain.GetHeight({ 10.0, 0.0f, 10.0f });
		height = mTerrain.GetHeight({ 15.0f, 0.0f, 20.0f });
		SetRenderGroupPosition(mCharacter2, { 15.0f,height,20.0f });

		mMirror.transform.position = Vector3(10, height+2, 15);
	}
	//Setting mirror camera position and direction
	Vector3 distanceFromCamera = mCamera.GetPosition() - mMirror.transform.position;
	Vector3 cameraPosition = (mMirror.transform.position - distanceFromCamera);
	cameraPosition.y = mCamera.GetPosition().y;
	mMirrorCamera.SetPosition(cameraPosition);
	mMirrorCamera.SetLookAt(mCamera.GetPosition());
	
	//Rotating character model to face other direction + rotating to face mirror direction
	Vector3 a = Math::Cross(mCamera.GetDirection(), Vector3::ZAxis);
	Quaternion q = Quaternion(a.x,-a.y,a.z, 1);
	q = Quaternion(0, 1, 0, 0) * q;
	SetRenderGroupRotation(mCharacter, Math::Normalize(q));

	//Setting character model to camera position
	Vector3 charPosition = mCamera.GetPosition();
	charPosition.y -= 1.5f;
	SetRenderGroupPosition(mCharacter, charPosition);
}

void GameState::Render()
{
	mShadowEffect.SetFocus(mCamera.GetPosition());

	mStandardEffect.SetCamera(mMirrorCamera);
	mTerrainEffect.SetCamera(mMirrorCamera);

	mPostProcessRenderTarget.BeginRender();
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
	mPostProcessRenderTarget.EndRender();
	
	mMirrorRenderTarget.BeginRender();
		mPostProcessingEffect.Begin();
			mPostProcessingEffect.Render(mScreenQuad);
		mPostProcessingEffect.End();
	mMirrorRenderTarget.EndRender();

	Texture& mirrorTexture = mMirrorRenderTarget;

	mStandardEffect.SetCamera(mCamera);
	mTerrainEffect.SetCamera(mCamera);

	mStandardEffect.Begin();
		mStandardEffect.Render(mMirror, mirrorTexture);
		DrawRenderGroup(mStandardEffect, mCharacter2);
	mStandardEffect.End();
	mTerrainEffect.Begin();
		mTerrainEffect.Render(mGround);
	mTerrainEffect.End();

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

		if (ImGui::CollapsingHeader("MirrorEffect", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("MirrorEffect");
			ImGui::Image(
				mMirrorRenderTarget.GetRawData(),
				{ 144,144 },
				{ 0,0 },
				{ 1,1 },
				{ 1,1,1,1 },
				{ 1,1,1,1 });
		}

		mStandardEffect.DebugUI();
		mTerrainEffect.DebugUI();
		mShadowEffect.DebugUI();
		mPostProcessingEffect.DebugUI();
	ImGui::End();
}