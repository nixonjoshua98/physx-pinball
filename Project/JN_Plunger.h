#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

using namespace physx;


namespace Actors
{
	class JN_Plunger
	{
	public:
		JN_Plunger(PxTransform pose = PxTransform(PxIdentity));

		void Activate(PxReal force);

		void AddToScene(JN_Scene* scene);

	private:
		Box* box;

		PxD6Joint* joint;
	};
}