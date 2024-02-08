#include "GameState.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Input;

void GameState::Initialize()
{
	//create a shape
	CreateShape();
	

	auto device = GraphicsSystem::Get()->GetDevice();
	//create a way to send data to gpu
	
	//we need a vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size()) * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = mVertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "GameState: Failed to create vertex data");

	//===============================================================
	//===============================================================
	
	//we need a index buffer
	bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(mIndices.size()) * sizeof(uint32_t);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	initData.pSysMem = mIndices.data();

	hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
	ASSERT(SUCCEEDED(hr), "GameState: Failed to create index data");
	
	//===============================================================
	//===============================================================
	// need to create a vertex shader
	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoSomething.fx";

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		shaderFilePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Gamestate: Failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader
	);
	ASSERT(SUCCEEDED(hr), "Gamestate: Failed to create vertex shader");
	//===============================================================
	//===============================================================
	// create the input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT }); 
	vertexLayout.push_back({ "COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(),
		static_cast<UINT>(vertexLayout.size()),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout
	);
	ASSERT(SUCCEEDED(hr), "Gamestate: Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	//===============================================================
	//===============================================================
	// last thing to create is a pixel shader
	hr = D3DCompileFromFile(
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
	mVertices.clear();
	SafeRelease(mPixelShader);
	SafeRelease(mInputLayout);
	SafeRelease(mVertexShader);
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);

}

void GameState::Update(float deltaTime)
{

}

void GameState::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f}, Colors::Blue });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f}, Colors::Green });
	mVertices.push_back({ {0.5f, -0.5f, 0.0f}, Colors::Yellow });
	
	//4 triangles, each with 3 vertices
	//each vertex is 7 floats
	//7 * 3 * 4 = 84 floats = 336 bytes
	//4 vertices = 7 floats
	//1 * 3 indices * 4 = 12 ints + 7 floats = 92 bytes

	mIndices = {
		0, 1, 2,
		0, 2, 3
	};
}

void GameState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	//bind
	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	context->PSSetShader(mPixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed((UINT)mIndices.size(), 0, 0);
	context->Draw(static_cast<UINT>(mVertices.size()), 0);
}
