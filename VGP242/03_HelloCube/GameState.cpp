#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	auto device = GraphicsSystem::Get()->GetDevice();

	//create a shape
	mMesh.vertices.push_back({ {-0.5f, -0.5f, 0.0f}, Colors::Red });
	mMesh.vertices.push_back({ { -0.5f, 0.5f, 0.0f}, Colors::Blue });
	mMesh.vertices.push_back({ { 0.5f, 0.5f, 0.0f}, Colors::Green });
	mMesh.vertices.push_back({ {0.5f, -0.5f, 0.0f}, Colors::Yellow });

	mMesh.indices = {
		0, 1, 2,
		0, 2, 3
	};
	
	mMeshBuffer.Initialize(mMesh);

	// need to create a vertex shader
	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoSomething.fx";
	mVertexShader.Initialize<VertexPC>(shaderFilePath);

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	//===============================================================
	//===============================================================
	// last thing to create is a pixel shader
	HRESULT hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Gamestate: Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader
	);
	ASSERT(SUCCEEDED(hr), "Gamestate: Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

}

void GameState::Terminate()
{
	mMeshBuffer.Terminate();
	SafeRelease(mPixelShader);
}

void GameState::Update(float deltaTime)
{

}

void GameState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	//bind
	mVertexShader.Bind();
	context->PSSetShader(mPixelShader, nullptr, 0);

	mMeshBuffer.Render();
}
