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
	for (PxU32 i = 0; i < count; i++)
	{
		const std::string trigger = std::string(pairs[i].triggerActor->getName());
		const std::string other = std::string(pairs[i].otherActor->getName());

		if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			if (other == "Ball" && trigger == "DeathTrigger")
			{
				dead_ball_trigger = true;
			}
		}

		else if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			if (other == "Ball" && trigger == "DeathTrigger")
			{
				score -= 100;

				std::cout << "Ball Out of Bounds\n";

				dead_ball_trigger = false;
			}
		}
	}
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
