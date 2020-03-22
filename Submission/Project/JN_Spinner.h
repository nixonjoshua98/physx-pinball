#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

#include "BasicActors.h"

namespace Actors
{
	// Thin object which rotates
	class JN_Spinner : public Box
	{
	public:
		// Constructor
		JN_Spinner(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f, PxReal velocity = 1.0f);

		// Add box to the scene
		void AddToScene(JN_Scene* scene);

	private:
		RevoluteJoint* joint;

		PxReal velocity;
	};
}

