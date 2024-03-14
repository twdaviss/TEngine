#pragma once

#include <TEngine/Inc/TEngine.h>

class GameStatePX : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual TEngine::Graphics::MeshPX DrawShape() = 0;
	virtual std::string GetTexturePath() = 0;

	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::MeshPX mMesh;
	TEngine::Graphics::ConstantBuffer mConstantBuffer;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::VertexShader mVertexShader;
	TEngine::Graphics::PixelShader mPixelShader;

	TEngine::Graphics::Texture mTexture;
	TEngine::Graphics::Sampler mSampler;
};

class GameStatePC : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual TEngine::Graphics::MeshPC DrawShape() = 0;
	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::MeshPC mMesh;
	TEngine::Graphics::ConstantBuffer mConstantBuffer;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::VertexShader mVertexShader;
	TEngine::Graphics::PixelShader mPixelShader;

	TEngine::Graphics::Texture mTexture;
	TEngine::Graphics::Sampler mSampler;
};

class SkyBoxState : public GameStatePX
{
protected:
	TEngine::Graphics::MeshPX DrawShape();
	std::string GetTexturePath();
};

class SkySphereState : public GameStatePX
{
protected:
	TEngine::Graphics::MeshPX DrawShape();
	std::string GetTexturePath();
};

class RectangleState : public GameStatePC
{
protected:
	TEngine::Graphics::MeshPC DrawShape();
};

class CubeState : public GameStatePC
{
protected:
	TEngine::Graphics::MeshPC DrawShape();
};

class SphereState : public GameStatePC
{
protected:
	TEngine::Graphics::MeshPC DrawShape();
};

class CylinderState : public GameStatePC
{
protected:
	TEngine::Graphics::MeshPC DrawShape();
};

class HorizontalPlaneState : public GameStatePC
{
protected:
	TEngine::Graphics::MeshPC DrawShape();
};



