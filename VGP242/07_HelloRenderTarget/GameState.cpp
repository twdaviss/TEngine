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
	mMesh = MeshBuilder::CreateSpherePX(100, 100, 1.0f);

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPX>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);
	mTexture.Initialize(L"../../Assets/Images/planets/earth/earth.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	mRenderTarget.Terminate();
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
	mCamera.SetAspectRatio(1.0f);
	mRenderTarget.BeginRender();
		RenderObject(mMeshBuffer);
	mRenderTarget.EndRender();

	mCamera.SetAspectRatio(0.0f);
	RenderObject(mMeshBuffer);

}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Render Target");
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 128,128 },
		{ 0,0 },
		{ 1,1 },
		{ 1,1,1,1 },
		{ 1,1,1,1 }
	);
	ImGui::End();

	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

}

void GameState::RenderObject(const MeshBuffer& meshBuffer)
{
	//bind
	mVertexShader.Bind();
	mPixelShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);

	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	meshBuffer.Render();
}


