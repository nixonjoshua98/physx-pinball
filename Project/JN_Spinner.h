#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

#include "BasicActors.h"

namespace Actors
{
	class JN_Spinner : public Box
	{
	public:
		JN_Spinner(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f, PxReal velocity = 1.0f);
		~JN_Spinner();

		void AddToScene(JN_Scene* scene);

	private:
		RevoluteJoint* joint;

		PxReal velocity;
	};
}

