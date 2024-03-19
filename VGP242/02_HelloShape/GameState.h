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
	virtual void CreateShape() {};
	struct Vertex
	{
		TEngine::Math::Vector3 position;
		TEngine::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};

class TriangleState : public SolarSystem
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class SquareState : public SolarSystem
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class TriforceState : public SolarSystem
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class PyramidState : public SolarSystem
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class DiamondState : public SolarSystem
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};
