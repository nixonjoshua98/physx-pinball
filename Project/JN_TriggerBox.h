#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

namespace Actors
{
	class JN_TriggerBox : public Box
	{
	public:
		JN_TriggerBox(const std::string& name, const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f);
		
		void AddToScene(JN_Scene* scene);
	};
}

