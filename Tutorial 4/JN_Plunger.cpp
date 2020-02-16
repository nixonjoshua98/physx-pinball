
#include "PxPhysicsAPI.h"

#include "JN_Plunger.h"

#include "JN_BasicActors.h"

#include "PhysicsEngine.h"

using namespace PhysicsEngine;


JN_Plunger::JN_Plunger(JN_Scene* scene)
{
	trampoline = new JN_Trampoline(
		PxTransform({ 7.25f, 0.0f, 14.75f }, PxQuat(90.0f, { -1.0, 0.0f, 0.0f })),
		{ 0.25f, 0.25f, 0.25f },
		100.0f,
		25.0f);

	trampoline->AddToScene(scene);
}

void JN_Plunger::Activate(PxReal force)
{
	trampoline->AddForce(force);
}
