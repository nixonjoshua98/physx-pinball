#include "JN_SimulationCallback.h"




#include <iostream>

JN_SimulationCallback::JN_SimulationCallback()
{
}

JN_SimulationCallback::~JN_SimulationCallback()
{
}

void JN_SimulationCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
}

void JN_SimulationCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	std::cout << "onContact\n";
}

void JN_SimulationCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
{
}

void JN_SimulationCallback::onWake(PxActor** actors, PxU32 count)
{
}

void JN_SimulationCallback::onSleep(PxActor** actors, PxU32 count)
{
}

void JN_SimulationCallback::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}
