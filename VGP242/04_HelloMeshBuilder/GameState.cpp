#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	auto device = GraphicsSystem::Get()->GetDevice();

	//create a shape
	//mMesh = MeshBuilder::CreatePyramidPC(2.0f);
	//mMesh = MeshBuilder::CreateCubePC(2.0f);
	//mMesh = MeshBuilder::CreateRectPC(2.0f, 0.5f, 1.0f);
	//mMesh = MeshBuilder::CreateVerticalPlanePC(10, 10, 1.0f);
	//mMesh = MeshBuilder::CreateHorizontalPlanePC(10, 10, 1.0f);
	//mMesh = MeshBuilder::CreateCylinderPC(100, 4);
	//mMesh = MeshBuilder::CreateSpherePC(100, 100, 1);

	mMesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
	mMesh.vertices.push_back({ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } });
	mMesh.vertices.push_back({ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } });
	mMesh.vertices.push_back({ {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });

	mMesh.indices = {
		0, 1, 2,
		0, 2, 3
	};

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mConstantBuffer.Initialize(sizeof(TMath::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPX>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);
	mTexture.Initialize(L"../../Assets/Images/misc/basketball.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	mTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
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
	//bind
	mVertexShader.Bind();
	mPixelShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);

	TMath::Matrix4 matWorld = TMath::Matrix4::Identity;
	TMath::Matrix4 matView = mCamera.GetViewMatrix();
	TMath::Matrix4 matProj = mCamera.GetProjectionMatrix();
	TMath::Matrix4 matFinal = matWorld * matView * matProj;
	TMath::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}
