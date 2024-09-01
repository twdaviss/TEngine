#pragma once

enum EventType
{
	None,
	AnimEvent,
	SpacePressedEvent,
};
class Event
{
public:
	Event() = delete;

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
	SpacePressedEvent() : Event(EventType::SpacePressedEvent);
};