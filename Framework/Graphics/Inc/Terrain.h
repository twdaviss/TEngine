#pragma once
#include "MeshTypes.h"

namespace TEngine::Graphics
{
	class Terrain final
	{
	public:
		void Initialize(const std::filesystem::path& fileName, float heightScale);
		void SetHeightScale(float heightScale);
		float GetHeightScale() const;
		float GetHeight(const Math::Vector3& position) const;
		const Mesh& GetMesh() const;
		float GetWidth() const;
		float GetLength() const;
	private:
		Mesh mMesh;
		uint32_t mRows = 0;
		uint32_t mColumns = 0;
		float mHeightScale = 35.0f;
	};
}
