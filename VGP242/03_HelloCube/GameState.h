#pragma once

#include <TEngine/Inc/TEngine.h>

class SolarSystem : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::MeshPC mMesh;
	TEngine::Graphics::ConstantBuffer mConstantBuffer;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::VertexShader mVertexShader;
	TEngine::Graphics::PixelShader mPixelShader;
};
