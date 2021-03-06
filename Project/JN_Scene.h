#pragma once


#include "PxPhysicsAPI.h"

#include "PhysicsEngine.h"

using namespace physx;
using namespace PhysicsEngine;

class JN_Scene
{
public:
	JN_Scene();

	// Init the scene
	void Init();

	// User defined initialisation
	virtual void CustomInit() {}

	// Perform a single simulation step
	void Update(PxReal delta);

	// User defined update step
	virtual void CustomUpdate(PxReal delta) {}

	// User defined render step
	virtual void CustomRender() {};

	// Add actor to the scene
	void Add(Actors::Actor* actor);

	// Get the PxScene object
	PxScene* Get();

	// Reset the scene
	void Reset();

	// Set pause
	void Pause(bool value);

	// Get pause
	bool Pause();

	// Highlight
	void HighlightActor(PxRigidDynamic* actor);

	// Unhighlight
	void UnHighlightActor(PxRigidDynamic* actor);

	// Get the selected dynamic actor on the scene
	PxRigidDynamic* GetSelectedActor();

	// Switch to the next dynamic actor
	void SelectNextActor();

	// Vector with all actors
	std::vector<PxActor*> GetAllActors();

protected:
	bool is_paused;

	PxScene* physics_scene;
	PxRigidDynamic* selected_actor;
	PxSimulationFilterShader filter_shader;

	std::vector<PxVec3> actor_colour;
};

