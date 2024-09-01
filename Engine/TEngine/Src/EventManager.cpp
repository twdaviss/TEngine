#include "Precompiled.h"
#include "EventManager.h"

using namespace TEngine;

namespace
{
	std::unique_ptr<EventManager> sEventManager;
}
void TEngine::EventManager::StaticInitialize()
{
    ASSERT(sEventManager == nullptr, "EventManager: is already initialized");
    sEventManager = std::make_unique<EventManager>();
}

void TEngine::EventManager::StaticTerminate()
{
}

EventManager* TEngine::EventManager::Get()
{
    ASSERT(sEventManager != nullptr, "EventManager: is not initialized");
    return nullptr;
}

void TEngine::EventManager::Broadcast(const Event* event)
{
    sEventManager->BroadcastPrivate(event);
}

TEngine::EventManager::~EventManager()
{
}

void TEngine::EventManager::Initialize()
{
    mEventListeners.clear();
}

void TEngine::EventManager::Terminate()
{
    mEventListeners.clear();

}

uint32_t TEngine::EventManager::AddListener(EventType eventType, const EventCallback& cb)
{
    mEventListeners[eventType][++mListenerId] = cb;
    return mListenerId;
}

void TEngine::EventManager::RemoveListener(EventType eventType, uint32_t listenerId)
{
    auto listenerIter = mEventListeners.find(eventType);
    if (listenerIter != mEventListeners.end())
    {
        auto iter = listenerIter->second.find(listenerId);
        if (iter != listenerIter->second.end())
        {
            listenerIter->second.erase(iter);
        }
    }
}

void TEngine::EventManager::BroadcastPrivate(const Event* event)
{
    auto& listeners = mEventListeners[event->GetType()];
    if (auto& cb : listeners)
    {
        cb.second(event);
    }
}
