#pragma once

namespace TEngine
{
	enum class EventType
	{
		None,
		AnimEvent,
		SpacePressedEvent,
	};
	class Event
	{
	public:
		Event() = delete;
		Event(EventType et) : mEventType(et) {}
		virtual ~Event() = default;

		EventType GetType() const { return mEventType; }
	private:
		EventType mEventType = EventType::None;
	};

	class AnimEvent : public Event
	{
	public:
		AnimEvent() : Event(EventType::AnimEvent) {}
		~AnimEvent() = default;

		Graphics::ModelId modelId = 0;
		std::string eventName = "";
	};

	class SpacePressedEvent : public Event
	{
	public:
		SpacePressedEvent() : Event(EventType::SpacePressedEvent){}
		~SpacePressedEvent() = default;
	};
}
