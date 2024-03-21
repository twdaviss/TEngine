#pragma once

#include <TEngine/Inc/TEngine.h>

class GameState : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	void RenderObject(const TEngine::Graphics::MeshBuffer& meshBuffer);

	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::MeshPX mMesh;
	TEngine::Graphics::ConstantBuffer mConstantBuffer;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::VertexShader mVertexShader;
	TEngine::Graphics::PixelShader mPixelShader;

	TEngine::Graphics::Texture mTexture;
	TEngine::Graphics::Sampler mSampler;

	TEngine::Graphics::RenderTarget mRenderTarget;
};

