#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameStatePX::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	auto device = GraphicsSystem::Get()->GetDevice();

	//create a shape
	
	//mMesh = MeshBuilder::CreateHorizontalPlanePX(10, 10 ,10);
	mMesh = DrawShape();
	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPX>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);

	std::string texturePath = GetTexturePath();
	 
	mTexture.Initialize(texturePath);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameStatePX::Terminate()
{
	mSampler.Terminate();
	mTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
}

void GameStatePX::Update(float deltaTime)
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

void GameStatePX::Render()
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

	mMeshBuffer.Render();
}

void GameStatePC::Initialize()
{
	mCamera.SetPosition({ 0.0f,1.0f,-3.0f });
	mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

	auto device = GraphicsSystem::Get()->GetDevice();

	//create a shape

	//mMesh = MeshBuilder::CreateHorizontalPlanePX(10, 10 ,10);
	mMesh = DrawShape();

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoSomething.fx";
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mMeshBuffer.Initialize(mMesh);
	mVertexShader.Initialize<VertexPC>(shaderFilePath);
	mPixelShader.Initialize(shaderFilePath);
	//mTexture.Initialize(L"../../Assets/Images/skybox/skybox_texture.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameStatePC::Terminate()
{
	mSampler.Terminate();
	mTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mConstantBuffer.Terminate();
}

void GameStatePC::Update(float deltaTime)
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

void GameStatePC::Render()
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

	mMeshBuffer.Render();
}

MeshPX SkyBoxState::DrawShape()
{
	return MeshBuilder::CreateSkyBoxPX(1000.0f);
}

std::string SkyBoxState::GetTexturePath()
{
	return "../../Assets/Images/skybox/skybox_texture.jpg";
}

MeshPC SphereState::DrawShape()
{
	return MeshBuilder::CreateSpherePC(60.0f, 60.f, 1.0f);
}

MeshPC RectangleState::DrawShape()
{
	return MeshBuilder::CreateRectPC(2,1,1);
}

MeshPC CylinderState::DrawShape()
{
	return MeshBuilder::CreateCylinderPC(10,10);
}

MeshPC CubeState::DrawShape()
{
	return MeshBuilder::CreateCubePC(1);
}

MeshPC HorizontalPlaneState::DrawShape()
{
	return MeshBuilder::CreateHorizontalPlanePC(10, 10,1);
}

MeshPX SkySphereState::DrawShape()
{
	return MeshBuilder::CreateSkySpherePX(1000,1000,10);
}

std::string SkySphereState::GetTexturePath()
{
	return "../../Assets/Images/skysphere/sky.jpg";
}
