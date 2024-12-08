#pragma once

namespace TEngine
{
	enum class ComponentID
	{
		Invalid,	// default value
		Transform,	// transform component for location data
		Camera,		// contains a camera for viewing
		FPSCamera,	// moves camera with fps controls
		Mesh,		// creates a mesh render object
		Model,		// creates a model render object
		Animator,	// manages and controls animations
		RigidBody,	// physics object that gets added to the physics world
		SoundEffect,// adds an array of sound effects to an object
		SoundBank,	// adds a single sound effect to an object
		UIText,		// adds a text UI component
		UISprite,	// adds a sprite to the UI
		UIButton,	// adds a button to the UI
		Count
	};

	enum class ServiceID
	{
		Invalid,	//default value	
		Camera,		//controls active camera
		Render,
		Physics,
		UIRender,
		Count
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeID() {return static_cast<uint32_t>(id);}\
	uint32_t GetTypeID() const override {return StaticGetTypeID();}