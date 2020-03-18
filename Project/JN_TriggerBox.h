#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

namespace Actors
{
	// Box object which is not rendered and acts as a trigger
	class JN_TriggerBox : public Box
	{
	public:
		// Contructor
		JN_TriggerBox(const std::string& name, const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f);
		
		// Add the trigger to the scene
		void AddToScene(JN_Scene* scene);
	};
}

