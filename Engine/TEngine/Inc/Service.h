#pragma once

#include "TypeIds.h"

namespace TEngine
{
	class GameWorld;

	class Service
	{
	public:
		Service() = default;
		virtual ~Service() = default;

		Service(const Service&) = delete;
		Service(const Service&&) = delete;

		Service& operator=(const Service&) = delete;
		Service& operator=(const Service&&) = delete;

		virtual uint32_t GetTypeID() const = 0;

		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		GameWorld& GetWorld() { return *mWorld; }

	private:
		friend class GameWorld;
		GameWorld* mWorld = nullptr;
	};
}
