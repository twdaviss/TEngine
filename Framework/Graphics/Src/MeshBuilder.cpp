#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace TEngine;
using namespace TEngine::Graphics;

MeshPC MeshBuilder::CreatePyramidPC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;
	srand(time(nullptr));
	int index = rand() % 100;
	//front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index)});
	mesh.vertices.push_back({ { 0.0f, hs, 0.0f }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs, -hs }, GetNextColor(index) });

	//back
	mesh.vertices.push_back({ { -hs, -hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs, hs }, GetNextColor(index) });

	//indices
	mesh.indices = {
		//front
		0, 1, 2,
		//right
		2, 1, 4,
		//back
		4, 1, 3,
		//left
		0, 3, 1,
		//bottom
		0, 2, 4,
		0, 4, 3
	};

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC meshPC;

	const float hs = size * 0.5f;
	
	//front
	meshPC.vertices.push_back({ {-hs, -hs, -hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ {-hs,  hs, -hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ { hs,  hs, -hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ { hs, -hs, -hs }, GetNextColor(index) });
	//back
	meshPC.vertices.push_back({ {-hs, -hs,  hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ {-hs,  hs,  hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ { hs,  hs,  hs }, GetNextColor(index) });
	meshPC.vertices.push_back({ { hs, -hs,  hs }, GetNextColor(index) });

	CreateCubeIndices(meshPC.indices);

	return meshPC;
}

Mesh MeshBuilder::CreateCube(float size)
{
	Mesh mesh;
	const float hs = size * 0.5f;
	const float q = 0.25f;
	const float q2 = 0.5f;
	const float q3 = 0.75f;
	const float t = 0.34f;
	const float t2 = 0.65f;

	//left
	mesh.vertices.push_back({ { hs, -hs, -hs}, -Math::Vector3::XAxis, Math::Vector3::ZAxis, { 0.0f, t2 } });
	mesh.vertices.push_back({ { hs,  hs, -hs}, -Math::Vector3::XAxis, Math::Vector3::ZAxis, { 0.0f, t } });
	mesh.vertices.push_back({ { hs,  hs,  hs}, -Math::Vector3::XAxis, Math::Vector3::ZAxis, { q, t } });
	mesh.vertices.push_back({ { hs, -hs,  hs}, -Math::Vector3::XAxis, Math::Vector3::ZAxis, { q, t2 } });

	//top
	mesh.vertices.push_back({ { hs,  hs,  hs},  Math::Vector3::YAxis, Math::Vector3::XAxis, { q, t } });
	mesh.vertices.push_back({ { hs,  hs, -hs},  Math::Vector3::YAxis, Math::Vector3::XAxis, { q, 0.0f } });
	mesh.vertices.push_back({ {-hs,  hs, -hs},  Math::Vector3::YAxis, Math::Vector3::XAxis, { q2, 0.0f } });
	mesh.vertices.push_back({ {-hs,  hs,  hs},  Math::Vector3::YAxis, Math::Vector3::XAxis, { q2, t } });

	//front
	mesh.vertices.push_back({ {-hs, -hs,  hs}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { q2, t2 } });
	mesh.vertices.push_back({ {-hs,  hs,  hs}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { q2, t } });
	mesh.vertices.push_back({ { hs,  hs,  hs}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { q, t } });
	mesh.vertices.push_back({ { hs, -hs,  hs}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { q, t2 } });

	//bottom
	mesh.vertices.push_back({ { hs, -hs,  hs}, -Math::Vector3::YAxis, -Math::Vector3::ZAxis, { q, t2 } });
	mesh.vertices.push_back({ { hs, -hs, -hs}, -Math::Vector3::YAxis, -Math::Vector3::ZAxis, { q, 1.0f } });
	mesh.vertices.push_back({ {-hs, -hs, -hs}, -Math::Vector3::YAxis, -Math::Vector3::ZAxis, { q2, 1.0f } });
	mesh.vertices.push_back({ {-hs, -hs,  hs}, -Math::Vector3::YAxis, -Math::Vector3::ZAxis, { q2, t2 } });

	//right
	mesh.vertices.push_back({ {-hs, -hs, -hs},  Math::Vector3::XAxis, -Math::Vector3::ZAxis, { q3, t2 } });
	mesh.vertices.push_back({ {-hs,  hs, -hs},  Math::Vector3::XAxis, -Math::Vector3::ZAxis, { q3, t } });
	mesh.vertices.push_back({ {-hs,  hs,  hs},  Math::Vector3::XAxis, -Math::Vector3::ZAxis, { q2, t } });
	mesh.vertices.push_back({ {-hs, -hs,  hs},  Math::Vector3::XAxis, -Math::Vector3::ZAxis, { q2, t2 } });

	//back
	mesh.vertices.push_back({ {-hs, -hs, -hs},  Math::Vector3::ZAxis, -Math::Vector3::XAxis, { q3, t2 } });
	mesh.vertices.push_back({ {-hs,  hs, -hs},  Math::Vector3::ZAxis, -Math::Vector3::XAxis, { q3, t } });
	mesh.vertices.push_back({ { hs,  hs, -hs},  Math::Vector3::ZAxis, -Math::Vector3::XAxis, { 1.0f, t } });
	mesh.vertices.push_back({ { hs, -hs, -hs},  Math::Vector3::ZAxis, -Math::Vector3::XAxis, { 1.0f, t2 } });

	mesh.indices = {
		//left
		2, 1, 0,
		2, 0, 3,
		//top
		6, 5, 4,
		6, 4, 7,
		//front
		8, 9, 10,
		11, 8, 10,
		//bottom
		12, 13, 14,
		15, 12, 14,
		//right
		16, 17, 18,
		19, 16, 18,
		//back
		22, 21, 20,
		22, 20, 23
	};

	return mesh;
}

MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC meshPC;
	const float hw = width * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth * 0.5f;

	//front 
	meshPC.vertices.push_back({ {-hw, -hh, -hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ {-hw,  hh, -hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ { hw,  hh, -hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ { hw, -hh, -hd}, GetNextColor(index) });
		
	meshPC.vertices.push_back({ {-hw, -hh,  hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ {-hw,  hh,  hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ { hw,  hh,  hd}, GetNextColor(index) });
	meshPC.vertices.push_back({ { hw, -hh,  hd}, GetNextColor(index) });

	CreateCubeIndices(meshPC.indices);

	return meshPC;
}

MeshPC MeshBuilder::CreateVerticalPlanePC(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float y = -hph;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, GetNextColor(index) });
			x += spacing;
		}
		x = -hpw;
		y += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPX MeshBuilder::CreateVerticalPlanePX(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPX mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float y = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, {u,v} });
			x += spacing;
			u += uInc;
		}
		x = -hpw;
		y += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

Mesh MeshBuilder::CreateVerticalPlane(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	Mesh mesh;

	const Math::Vector3& up = Math::Vector3::YAxis;
	const Math::Vector3& right = Math::Vector3::XAxis;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float y = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, up, right, {u,v} });
			x += spacing;
			u += uInc;
		}
		x = -hpw;
		y += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateHorizontalPlanePC(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float z = -hph;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, GetNextColor(index) });
			x += spacing;
		}
		x = -hpw;
		z += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPX MeshBuilder::CreateHorizontalPlanePX(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPX mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, {u,v} });
			x += spacing;
			u += uInc;
		}
		x = -hpw;
		z += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

Mesh MeshBuilder::CreateHorizontalPlane(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	Mesh mesh;

	const Math::Vector3& up = Math::Vector3::YAxis;
	const Math::Vector3& right = Math::Vector3::XAxis;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, up, right, {u,v} });
			x += spacing;
			u += uInc;
		}
		x = -hpw;
		z += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(uint32_t slices, uint32_t rings)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float hh = static_cast<float>(rings) * 0.5f;

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = (slicePos / static_cast<float>(slices)) * Math::Constants::TwoPi;

			mesh.vertices.push_back({ {
				cos(rotation),
				ringPos - hh,
				sin(rotation) },
				GetNextColor(index)
				});
		}
	}

	mesh.vertices.push_back({ {0.0f, hh, 0.0f}, GetNextColor(index) });
	mesh.vertices.push_back({ {0.0f, -hh, 0.0f}, GetNextColor(index) });

	CreatePlaneIndices(mesh.indices, rings, slices);
	uint32_t bottomIndex = mesh.vertices.size() - 1;
	uint32_t topIndex = bottomIndex - 1;

	for (uint32_t s = 0; s < slices; ++s)
	{
		//bottom triangle
		mesh.indices.push_back(bottomIndex);
		mesh.indices.push_back(s);
		mesh.indices.push_back(s + 1);

		//top triangle
		uint32_t topRowIndex = topIndex - slices - 1 + s;
		mesh.indices.push_back(topIndex);
		mesh.indices.push_back(topRowIndex + 1);
		mesh.indices.push_back(topRowIndex);
	}

	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(uint32_t slices, uint32_t rings, float radius)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

	for(uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		float phi = ringPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi) },
					GetNextColor(index)
			});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(uint32_t slices, uint32_t rings, float radius)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPX mesh;

	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	const float uInc = 1.0f / static_cast<float>(slices);
	const float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		float phi = ringPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			float u = 1.0f - (uInc * slicePos);
			float v = vInc * ringPos;

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi) },
					{u, v} });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSkySpherePX(uint32_t slices, uint32_t rings, float radius)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPX mesh;

	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	const float uInc = 1.0f / static_cast<float>(slices);
	const float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		float phi = ringPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			float u = 1.0f - (uInc * slicePos);
			float v = vInc * ringPos;

			mesh.vertices.push_back({ {
					radius* cos(rotation)* sin(phi),
					radius * cos(phi),
					radius* sin(rotation)* sin(phi) },
					{u, v} });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

Mesh MeshBuilder::CreateSkySphere(uint32_t slices, uint32_t rings, float radius)
{
	Mesh mesh;

	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	const float uInc = 1.0f / static_cast<float>(slices);
	const float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		float phi = ringPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			float u = 1.0f - (uInc * slicePos);
			float v = vInc * ringPos;

			float x = radius * cos(rotation) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * sin(rotation) * sin(phi);

			Math::Vector3 position = { x, y, z };
			Math::Vector3 normal = Math::Normalize(position);
			Math::Vector3 tangent = Math::Normalize({ -z, 0.0f, x });
			Math::Vector2 uvCoord = { u, v };

			mesh.vertices.push_back({
				position,
				normal,
				tangent,
				uvCoord });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSkyBoxPX(float size)
{
	MeshPX mesh;
	const float hs = size * 0.5f;
	const float q = 0.25f;
	const float q2 = 2.0f * q;
	const float q3 = 3.0f * q;
	const float t = 1.0f / 3.0f;
	const float t2 = 2.0f * t;

	//left
	mesh.vertices.push_back({ { hs, -hs, -hs}, {0.0f, t2} });
	mesh.vertices.push_back({ { hs,  hs, -hs}, {0.0f, t} });
	mesh.vertices.push_back({ { hs,  hs,  hs}, {q, t} });
	mesh.vertices.push_back({ { hs, -hs,  hs}, {q, t2} });
										 
	//top								 
	mesh.vertices.push_back({ { hs,  hs,  hs}, {q, t} });
	mesh.vertices.push_back({ { hs,  hs, -hs}, {q, 0.0f} });
	mesh.vertices.push_back({ {-hs,  hs, -hs}, {q2, 0.0f} });
	mesh.vertices.push_back({ {-hs,  hs,  hs}, {q2, t} });
										 
	//front 							 
	mesh.vertices.push_back({ {-hs, -hs,  hs}, {q2, t2} });
	mesh.vertices.push_back({ {-hs,  hs,  hs}, {q2, t} });
	mesh.vertices.push_back({ { hs,  hs,  hs}, {q, t} });
	mesh.vertices.push_back({ { hs, -hs,  hs}, {q, t2} });
										 
	//bottom								 
	mesh.vertices.push_back({ { hs, -hs,  hs}, {q, t2} });
	mesh.vertices.push_back({ { hs, -hs, -hs}, {q, 1.0f} });
	mesh.vertices.push_back({ {-hs, -hs, -hs}, {q2, 1.0f} });
	mesh.vertices.push_back({ {-hs, -hs,  hs}, {q2, t2} });

	//right
	mesh.vertices.push_back({ {-hs, -hs, -hs}, {q3, t2} });
	mesh.vertices.push_back({ {-hs,  hs, -hs}, {q3, t} });
	mesh.vertices.push_back({ {-hs,  hs,  hs}, {q2, t} });
	mesh.vertices.push_back({ {-hs, -hs,  hs}, {q2, t2} });

	//back
	mesh.vertices.push_back({ {-hs, -hs, -hs}, {q3, t2} });
	mesh.vertices.push_back({ {-hs,  hs, -hs}, {q3, t} });
	mesh.vertices.push_back({ { hs,  hs, -hs}, {1.0f, t} });
	mesh.vertices.push_back({ { hs, -hs, -hs}, {1.0f, t2} });

	mesh.indices = {
		//left
		2, 1, 0,
		2, 0, 3,
		//top
		6, 5, 4,
		6, 4, 7,
		//front
		8, 9, 10,
		11, 8, 10,
		//bottom
		12, 13, 14,
		15, 12, 14,
		//right
		16, 17, 18,
		19, 16, 18,
		//back
		22, 21, 20,
		22, 20, 23
	};

	return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
	MeshPX mesh;
	mesh.vertices.push_back({ { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } });
	mesh.vertices.push_back({ {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } });
	mesh.vertices.push_back({ {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });
	mesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
	
	mesh.indices = { 0, 1, 3, 1, 2, 3 };

	return mesh;
}

Mesh TEngine::Graphics::MeshBuilder::CreateSpriteQuad(float width, float height)
{
	Mesh mesh;

	const float hw = width * 0.5f;
	const float hh = height * 0.5f;

	mesh.vertices.push_back({ { -hw, -hh, 0.0f }, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { 0.0f, 1.0f } });
	mesh.vertices.push_back({ { -hw,  hh, 0.0f }, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { 0.0f, 0.0f } });
	mesh.vertices.push_back({ {  hw,  hh, 0.0f }, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { 1.0f, 0.0f } });
	mesh.vertices.push_back({ {  hw, -hh, 0.0f }, -Math::Vector3::ZAxis, Math::Vector3::XAxis, { 1.0f, 1.0f } });

	mesh.indices = {
		0,1,2,
		0,2,3
	};

	return mesh;
}

Mesh MeshBuilder::CreateSphere(uint32_t slices, uint32_t rings, float radius)
{
	Mesh mesh;

	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	const float uInc = 1.0f / static_cast<float>(slices);
	const float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float ringPos = static_cast<float>(r);
		float phi = ringPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			float u = 1.0f - (uInc * slicePos);
			float v = vInc * ringPos;

			float x = radius * sin(rotation) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * cos(rotation) * sin(phi);

			Math::Vector3 position = { x,y,z };
			Math::Vector3 normal = Math::Normalize(position);
			Math::Vector3 tangent = Math::Normalize({ -z, 0.0f, x });
			Math::Vector2 uvCoord = { u,v };

			mesh.vertices.push_back({
				position,
				normal,
				tangent,
				uvCoord });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

