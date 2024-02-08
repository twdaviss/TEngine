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
	mPixelShader.Initialize(shaderFilePath);

}

void GameState::Terminate()
{
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{

}

void GameState::Render()
{
	//bind
	mVertexShader.Bind();
	mPixelShader.Bind();
	mMeshBuffer.Render();
}
