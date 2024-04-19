#pragma once

#include "MeshTypes.h"

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::Red,
			Colors::Yellow,
			Colors::Pink,
			Colors::Green,
			Colors::Purple,
			Colors::Orange,
			Colors::Blue,
		};
		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			//front
			0, 1, 2,
			0, 2, 3,
			//left
			4, 5, 1,
			4, 1, 0,
			//right
			3, 2, 6,
			3, 6, 7,
			//back
			7, 6, 5,
			7, 5, 4,
			//top
			1, 5, 6,
			1, 6, 2,
			//bottom
			0, 3, 7,
			0, 7, 4
		};
	}

	void CreatePlaneIndices(std::vector<uint32_t>& indices, uint32_t numRows, uint32_t numCols)
	{
		for (uint32_t r = 0; r < numRows; ++r)
		{
			for (uint32_t c = 0; c < numCols; ++c)
			{
				uint32_t i = (r * (numCols + 1)) + c;

				// triangle 1
				indices.push_back(i);
				indices.push_back(i + numCols + 2);
				indices.push_back(i + 1);

				// triangle 2
				indices.push_back(i);
				indices.push_back(i + numCols + 1);
				indices.push_back(i + numCols + 2);
			}
		}
	}
}


namespace TEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// pyramid
		static MeshPC CreatePyramidPC(float size);

		//cube
		static MeshPC CreateCubePC(float size);

		//rectangle
		static MeshPC CreateRectPC(float width, float height, float depth);

		//vertical plane
		static MeshPC CreateVerticalPlanePC(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPX CreateVerticalPlanePX(uint32_t numRows, uint32_t numCols, float spacing);

		//horizontal plane
		static MeshPC CreateHorizontalPlanePC(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPX CreateHorizontalPlanePX(uint32_t numRows, uint32_t numCols, float spacing);

		//cylinder
		static MeshPC CreateCylinderPC(uint32_t slices, uint32_t rings);

		//sphere
		static MeshPC CreateSpherePC(uint32_t slices, uint32_t rings, float radius);
		static MeshPX CreateSpherePX(uint32_t slices, uint32_t rings, float radius);
		static Mesh CreateSphere(uint32_t slices, uint32_t rings, float radius);

		//sky boxes
		static MeshPX CreateSkySpherePX(uint32_t slices, uint32_t rings, float radius);
		static MeshPX CreateSkyBoxPX(float size);


	};
}