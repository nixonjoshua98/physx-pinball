#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

#include "BasicActors.h"

#include "PxPhysicsAPI.h"

using namespace physx;

namespace Actors
{
	class JN_Paddle : public Actors::Capsule
	{
	public:
		// Constructor
		JN_Paddle(const PxTransform& pose = PxTransform(PxIdentity), PxVec2 dimensions = PxVec2(1.f, 1.f), PxReal offset = 0.0f, PxReal density = 1.f);

		// Add capsule to the object
		void AddToScene(JN_Scene* scene);

		// Add force
		void Activate(PxReal force);

	private:
		RevoluteJoint* joint;
	};
}

