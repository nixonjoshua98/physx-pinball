#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

using namespace physx;
using namespace Actors;

class JN_Plunger
{
public:
	JN_Plunger(PxTransform pose = PxTransform(PxIdentity));

	// Trigger the plunger
	void Activate(PxReal force);

	void AddToScene(JN_Scene* scene);

private:
	Box* top;

	PxD6Joint* joint;
};

