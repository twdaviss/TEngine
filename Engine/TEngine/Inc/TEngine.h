#pragma once

#include "Common.h"

#include "App.h"

#include "AppState.h"

#include "Event.h"
#include "EventManager.h"

//Game Object
#include "GameObject.h"

//Components
#include "TypeIds.h"
#include "Component.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"

namespace TEngine
{
	App& MainApp();
}