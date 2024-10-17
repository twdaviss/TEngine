#pragma once

namespace TEngine
{
	enum class ComponentID
	{
		Invalid,	//default value
		Transform,	//transform component for location data
		Camera,		//contains a camera for viewing
		FPSCamera,	//moves camera with fps controls	
		Count
	};

	enum class ServiceID
	{
		Invalid,	//default value	
		Camera,		//controls active camera
		Count
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeID() {return static_cast<uint32_t>(id);}\
	uint32_t GetTypeID() const override {return StaticGetTypeID();}