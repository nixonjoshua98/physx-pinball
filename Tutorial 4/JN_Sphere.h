#pragma once

#include "PxPhysicsAPI.h"

#include "JN_BaseActors.h"

using namespace physx;

namespace Actors
{
	class JN_Sphere : public DynamicActor
	{
	public:
		JN_Sphere(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal density = 1.f);

		void SetTrigger(bool value, PxReal index = -1);
	};
}