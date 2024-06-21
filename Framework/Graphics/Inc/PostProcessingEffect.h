#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace TEngine::Graphics
{
	class Texture;
	struct RenderObject;

	class PostProcessingEffect
	{
	public:
		enum class Mode
		{
			None,
			Monochrome,
			Invert,
			Mirror,
			Blur,
			Combine2,
			ChromaticAberration,
			Wave
		};

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void Render(const RenderObject& renderObject, const Texture& texture);

		void DebugUI();

		void SetMode(Mode mode);
		void SetTexture(const Texture* texture, uint32_t slot = 0);

	private:
		struct PostProcessData
		{
			int mode = 0;
			float params0 = 0.0f;
			float params1 = 0.0f;
			float params2 = 0.0f;
		};

		using PostProcessingBuffer = TypedConstantBuffer<PostProcessData>;
		PostProcessingBuffer mPostProcessingBuffer;

		Sampler mSampler;
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		std::array<const Texture*, 4> mTextures;

		Mode mMode = Mode::None;
		float mMirrorX = 1.0f;
		float mMirrorY = 1.0f;
		float mBlurStrength = 5.0f;
		float mAberrationValue = 0.005f;
		float mWaveLength = 0.05f;
		float mNumWaves = 20.0f;
		float mUVOffsetX = 0.0f;
	};
}