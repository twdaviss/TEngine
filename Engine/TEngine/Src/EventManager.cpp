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
    if (sEventManager != nullptr)
    {
        sEventManager->Terminate();
        sEventManager.reset();
    }
}

EventManager* TEngine::EventManager::Get()
{
    ASSERT(sEventManager != nullptr, "EventManager: is not initialized");
    return sEventManager.get();
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

ListenerId TEngine::EventManager::AddListener(EventType eventType, const EventCallback& cb)
{
    mEventListeners[eventType][++mListenerId] = cb;
    return mListenerId;
}

void TEngine::EventManager::RemoveListener(EventType eventType, ListenerId listenerId)
{
    auto listenersIter = mEventListeners.find(eventType);
    if (listenersIter != mEventListeners.end())
    {
        auto iter = listenersIter->second.find(listenerId);
        if (iter != listenersIter->second.end())
        {
            listenersIter->second.erase(iter);
        }
    }
}

void TEngine::EventManager::BroadcastPrivate(const Event* event)
{
    auto listenersIter = mEventListeners.find(event->GetType());
    if (listenersIter != mEventListeners.end())
    {
        for (auto& cb : listenersIter->second)
        {
            cb.second(event);
        }
    }
}
