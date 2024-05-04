#include <TEngine/Inc/TEngine.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace TEngine;
using namespace TEngine::Graphics;
using namespace TEngine::Math;

struct Arguments
{
	std::filesystem::path inputFileName;
	std::filesystem::path outputFileName;
	float scale = 1.0f;
};

Vector3 ToVector3(const aiVector3D& v)
{
	return {
		static_cast<float>(v.x),
		static_cast<float>(v.y),
		static_cast<float>(v.z)
	};
}

Vector2 ToTexCoord(const aiVector3D& v)
{
	return {
		static_cast<float>(v.x),
		static_cast<float>(v.y),
	};
}

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		return std::nullopt;
	}

	Arguments args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];
	for (int i = 1; i + 2 < argc; ++i)
	{
		if (strcmp(argv[i], "-scale") == 0)
		{
			args.scale = atof(argv[i + 1]);
			++i;
		}
	}
	return args;
}

int main(int argc, char* argv[])
{
	const auto argOpt = ParseArgs(argc, argv);
	if (argOpt.has_value() == false)
	{
		printf("No arguments present in the import fbx model...\n");
		return -1;
	}
	const Arguments& args = argOpt.value();
	Assimp::Importer importer;
	const uint32_t flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded;
	const aiScene* scene = importer.ReadFile(args.inputFileName.u8string().c_str(), flags);
	if (scene == nullptr)
	{
		printf("Error: %s...\n", importer.GetErrorString());
		return -1;
	}

	printf("Importing %s...\n", args.inputFileName.u8string().c_str());

	Model model;
	
	if (scene->HasMeshes())
	{
		printf("Reading mesh data...\n");
		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			const aiMesh*
			assimpMesh = scene->mMeshes[meshIndex];
			if (assimpMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				continue;
			}
			
			const uint32_t numVertices = assimpMesh->mNumVertices;
			const uint32_t numFaces = assimpMesh->mNumFaces;
			const uint32_t numIndices = assimpMesh->mNumFaces * 3;

			Model::MeshData& meshData = model.meshData.emplace_back();

			printf("Reading material index...\n");
			meshData.materialIndex = assimpMesh->mMaterialIndex;

			printf("Reading vertices...\n");
			Mesh& mesh = meshData.mesh;
			mesh.vertices.reserve(numVertices);

			const aiVector3D* positions = assimpMesh->mVertices;
			const aiVector3D* normals = assimpMesh->mNormals;
			const aiVector3D* tangents = assimpMesh->HasTangentsAndBitangents() ? assimpMesh->mTangents : nullptr;
			const aiVector3D* texCoords = assimpMesh->HasTextureCoords(0) ? assimpMesh->mTextureCoords[0] : nullptr;
			for (uint32_t v = 0; v < numVertices; ++v)
			{
				Vertex& vertex = mesh.vertices.emplace_back();
				vertex.position = ToVector3(positions[v]) * args.scale;
				vertex.normal = ToVector3(normals[v]);
				vertex.tangent = tangents ? ToVector3(tangents[v]) : Vector3::Zero;
				vertex.uvCoord = tangents ? ToTexCoord(tangents[v]) : Vector2::Zero;
			}

			printf("Reading Indices...\n");
			mesh.indices.reserve(numIndices);
			const aiFace* aiFaces = assimpMesh->mFaces;
			for (uint32_t f = 0; f < numFaces; ++f)
			{
				const aiFace& assimpFace = aiFaces[f];
				for (uint32_t i = 0; i < 3; ++i)
				{
					mesh.indices.push_back(assimpFace.mIndices[i]);
				}
			}
		}
	}
	printf("Saving Model...\n");
	if (!ModelIO::SaveModel(args.outputFileName, model));

	return 0;
}