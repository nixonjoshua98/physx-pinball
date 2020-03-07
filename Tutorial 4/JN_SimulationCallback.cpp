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
	std::cout << "onTrigger\n";
}

void JN_SimulationCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	for (PxU32 i = 0; i < nbPairs; i++)
	{
		// Check if eNOTIFY_TOUCH_FOUND is in the events
		if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			const std::string actor1name = pairHeader.actors[0]->getName();
			const std::string actor2name = pairHeader.actors[1]->getName();

			std::cout << actor1name << " hit " << actor2name << std::endl;

			if (actor1name == "Hexagon" || actor2name == "Hexagon")
			{
				score += 500;
			}
			else if (actor1name == "Paddle" || actor2name == "Paddle")
			{
				score += 100;
			}
			else if (actor1name == "Spinner" || actor2name == "Spinner")
			{
				score += 250;
			}

			std::cout << "Score: " << score << std::endl;
		}
	}
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
