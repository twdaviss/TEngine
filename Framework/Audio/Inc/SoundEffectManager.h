#pragma once

namespace TEngine::Audio
{
	using SoundId = std::size_t;

	class SoundEffectManager final
	{
	public:
		static void StaticInitialize(const std::filesystem::path& root);
		static void StaticTerminate();
		static SoundEffectManager* Get();

		SoundEffectManager() = default;
		~SoundEffectManager();

		SoundEffectManager(const SoundEffectManager&) = delete;
		SoundEffectManager(const SoundEffectManager&&) = delete;
		SoundEffectManager& operator=(const SoundEffectManager&) = delete;
		SoundEffectManager& operator=(const SoundEffectManager&&) = delete;

		void SetRootPath(const std::filesystem::path& root);

		SoundId Load(const std::filesystem::path& fileName);
		void Clear();

		void Play(SoundId id, bool loop = false);
		void Stop(SoundId id);

	private:
		struct Entry
		{
			std::unique_ptr<DirectX::SoundEffect> effect;
			//noteL make this a vector if multiple instance are desired
			std::unique_ptr<DirectX::SoundEffectInstance> instance;
		};

		using SoundEffects = std::unordered_map<SoundId, std::unique_ptr<Entry>>;
		SoundEffects mInventory;

		std::filesystem::path mRoot;
	};
}
