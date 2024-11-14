#pragma once

#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "Material.h"
#include "PixelShader.h"
#include "RenderTarget.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace TEngine::Graphics
{
	class Camera;
	class Texture;
	struct RenderObject;

	class StandardEffect
	{
	public:
		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void Render(const RenderObject& renderObject, const Texture& texture);

		void SetCamera(const Camera& camera);
		void SetLightCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetShadowMap(const Texture& shadowMap);

		void DebugUI();

	private:
		struct TransformData
		{
			Math::Matrix4 wvp;
			Math::Matrix4 lwvp;
			Math::Matrix4 world;
			Math::Vector3 viewPosition;
			float padding = 0.0f;
		};

		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useNormalMap = 1;
			int useSpecMap = 1;
			int useLighting = 1;
			int useBumpMap = 1;
			int useShadowMap = 1;
			int useSkinning = 1;
			float bumpWeight = 1.0f;
			float depthBias = 0.0001f;
			float padding[3] = { 0.0f };
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using BoneTransformBuffer = ConstantBuffer;

		TransformBuffer mTransformBuffer;
		SettingsBuffer mSettingsBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		BoneTransformBuffer mBoneTransformBuffer;
		Sampler mSampler;
		VertexShader mVertexShader;
		PixelShader mPixelShader;

		SettingsData mSettingsData;
		const Camera* mCamera = nullptr;
		const Camera* mLightCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
		const Texture* mShadowMap = nullptr;
	};
}