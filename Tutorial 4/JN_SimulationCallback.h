#pragma once

#include "PxPhysicsAPI.h"

using namespace physx;

class JN_SimulationCallback : public PxSimulationEventCallback
{
public:
	JN_SimulationCallback();
	~JN_SimulationCallback();

	bool dead_ball_trigger = false;

	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);
	virtual void onWake(PxActor** actors, PxU32 count);
	virtual void onSleep(PxActor** actors, PxU32 count);
	virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);

private:
	int score = 0;
};

