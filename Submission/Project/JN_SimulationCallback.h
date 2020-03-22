#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

class JN_SimulationCallback : public PxSimulationEventCallback
{
public:
	// Flag for when the ball goes out of bounds
	bool dead_ball_trigger = false;

	// Called when a trigger is involved in collision
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);

	// Object collides with object
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

	// These are required to be created
	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {};
	virtual void onWake(PxActor** actors, PxU32 count) {};
	virtual void onSleep(PxActor** actors, PxU32 count) {};
	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {};

	// Score...
	int score = 0;
};

