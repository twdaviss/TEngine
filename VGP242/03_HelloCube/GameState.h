#pragma once

#include <TEngine/Inc/TEngine.h>

class GameState : public TEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();
	struct Vertex
	{
		TEngine::TMath::Vector3 position;
		TEngine::Color color;
	};
	
	using Indices = std::vector<uint32_t>;
	using Vertices = std::vector<Vertex>;
	Vertices mVertices;
	Indices mIndices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11Buffer* mIndexBuffer = nullptr;

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};
