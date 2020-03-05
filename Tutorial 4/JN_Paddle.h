#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

#include "BasicActors.h"

#include "PxPhysicsAPI.h"

using namespace physx;

namespace Actors
{
	class JN_Paddle : public Actors::Box
	{
	public:
		JN_Paddle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f);
		~JN_Paddle();

		void AddToScene(JN_Scene* scene);

		void Activate(PxReal force);

	private:
		RevoluteJoint* joint;
	};
}

