#pragma once

#include <TEngine/Inc/TEngine.h>

class Planet
{
public:
	Planet() {};
	void Initialize(std::string _name, int _radius, int _orbitDist, float _rotationSpeed, float _orbitSpeed, std::string _texturePath);
	void Terminate();
	void Update(float deltaTime);
	void Render();
	Matrix4 worldMatrix = Matrix4::Identity;
	TEngine::Graphics::MeshPX mMesh;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::Texture mTexture;
protected:
	int radius;
	int orbitDist;
	float orbitSpeed;
	float rotationSpeed;
	std::string texturePath;
	std::string name;
};

class SolarSystem : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
	void InitializePlanets();
	void TerminatePlanets();
	void UpdatePlanets(float deltaTime);
	void RenderPlanets();

protected:
	TEngine::Graphics::Camera mCamera;
	TEngine::Graphics::MeshPX mMesh;
	TEngine::Graphics::ConstantBuffer mConstantBuffer;
	TEngine::Graphics::MeshBuffer mMeshBuffer;
	TEngine::Graphics::VertexShader mVertexShader;
	TEngine::Graphics::PixelShader mPixelShader;

	TEngine::Graphics::Texture mTexture;
	TEngine::Graphics::Sampler mSampler;

	Planet sun;
	Planet mercury;
	Planet venus;
	Planet earth;
	Planet mars;
	Planet jupiter;
	Planet saturn;
	Planet uranus;
	Planet neptune;

};

