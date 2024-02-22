#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::TMath::Constants;

namespace
{
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Vector3& v0, const Vector3& v1, const Color& color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color);

		void Render(const Camera& camera);

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFaceVertices;
		uint32_t mLineVerticesCount = 0;
		uint32_t mFaceVerticesCount = 0;
		uint32_t mMaxVertexCount = 0;
	};
	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount)
	{
		std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";
		mVertexShader.Initialize<VertexPX>(shaderPath);
		mPixelShader.Initialize(shaderPath);
		mConstantBuffer.Initialize(sizeof(TMath::Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);

		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVerticesCount = 0;
		mFaceVerticesCount = 0;
		mMaxVertexCount = maxVertexCount;
	}
	void SimpleDrawImpl::Terminate()
	{
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}
	void SimpleDrawImpl::AddLine(const Vector3& v0, const Vector3& v1, const Color& color)
	{}
	void SimpleDrawImpl::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color)
	{}
	void SimpleDrawImpl::Render(const Camera& camera)
	{}
}


void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
}

void SimpleDraw::StaticTerminate()
{
}

void SimpleDraw::AddLine(const Vector3& v0, const Vector3& v1, const Color& color)
{
}

void SimpleDraw::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color)
{
}

void SimpleDraw::AddAABB(const Vector3& min, const Vector3& max, const Color& color)
{
}

void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
}

void SimpleDraw::AddFilledAABB(const Vector3& min, const Vector3& max, const Color& color)
{
}

void SimpleDraw::AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color)
{
}

void SimpleDraw::AddSphere(uint32_t slices, uint32_t rings, float radius, const Color& color)
{
}

void SimpleDraw::AddGroundPlane(float size, const Color& color)
{
}

void SimpleDraw::AddGroundCircle(uint32_t slices, float radius, const Color& color)
{
}

void SimpleDraw::AddTransform(const Matrix4& matrix)
{
}

void SimpleDraw::Render(const Camera& camera)
{
}
