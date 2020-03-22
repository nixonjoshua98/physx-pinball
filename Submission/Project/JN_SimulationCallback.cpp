#include "JN_SimulationCallback.h"

#include <iostream>

void JN_SimulationCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for (PxU32 i = 0; i < count; i++)
	{
		const std::string trigger = std::string(pairs[i].triggerActor->getName());
		const std::string other = std::string(pairs[i].otherActor->getName());

		// On trigger enter
		if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			if (other == "Ball" && trigger == "DeathTrigger")
			{
				dead_ball_trigger = true;
			}
		}

		// On trigger exit
		else if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			if (other == "Ball" && trigger == "DeathTrigger")
			{
				score -= 250;

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

			// Ignore non-ball collisions
			if (!(actor1name == "Ball" || actor2name == "Ball"))
				continue;
			
			// Ball collided with a hexagon
			if (actor1name == "Hexagon" || actor2name == "Hexagon")
			{
				score += 500;
			}

			// Collided with a paddle
			else if (actor1name == "Paddle" || actor2name == "Paddle")
			{
				score += 100;
			}

			// Collided with a spinner
			else if (actor1name == "Spinner" || actor2name == "Spinner")
			{
				score += 250;
			}
		}
	}
}