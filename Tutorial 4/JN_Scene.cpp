
#include <vector>

#include "JN_Scene.h"

#include <iostream>

static PxFilterFlags CustomFilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize
)
{
	// let triggers through
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;

		return PxFilterFlags();
	}

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;


	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
	{
		//Trigger onContact callback for this pair of objects

		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
	}

	return PxFilterFlags();
}


JN_Scene::JN_Scene() : filter_shader(CustomFilterShader)
{

}

void JN_Scene::Init()
{
	PxSceneDesc scene_desc(GetPhysics()->getTolerancesScale());
	
	// Set number of CPU threads
	if (!scene_desc.cpuDispatcher)
	{
		scene_desc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	}

	// Set shader
	scene_desc.filterShader = filter_shader;

	// Continous collision - stops the ball going through objects
	scene_desc.flags |= PxSceneFlag::eENABLE_CCD;

	// Create the scene for the physics world from the description
	physics_scene = GetPhysics()->createScene(scene_desc);

	if (!physics_scene)
		throw new Exception("Physics scene failed to be created.");

	// Earth gravity: (0.0f, -9.81f, 0.0f)
	physics_scene->setGravity(PxVec3(0.0f, -9.81, 2.5));

	CustomInit();

	is_paused = false;

	selected_actor = 0;

	SelectNextActor();
}

void JN_Scene::Update(PxReal delta)
{
	if (!is_paused)
	{
		CustomUpdate(delta);

		physics_scene->simulate(delta);

		// Save the simulation results
		physics_scene->fetchResults(true);
	}
}

void JN_Scene::Add(Actors::Actor* actor)
{
	physics_scene->addActor(*actor->Get());
}

PxScene* JN_Scene::Get()
{
	return physics_scene;
}

void JN_Scene::Reset()
{
	physics_scene->release();

	Init();
}

void JN_Scene::Pause(bool value)
{
	is_paused = value;
}

bool JN_Scene::Pause()
{
	return is_paused;
}

void JN_Scene::HighlightActor(PxRigidDynamic* actor)
{
	std::vector<PxShape*> shapes(actor->getNbShapes());

	actor->getShapes((PxShape * *)& shapes.front(), (PxU32)shapes.size());

	actor_colour.clear();

	// Update the colour
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		PxVec3* color = ((UserData*)shapes[i]->userData)->color;

		actor_colour.push_back(*color);

		*color += PxVec3(.2f, .2f, .2f);
	}
}

void JN_Scene::UnHighlightActor(PxRigidDynamic* actor)
{
	// Restore the original color
	std::vector<PxShape*> shapes(actor->getNbShapes());

	actor->getShapes((PxShape * *)& shapes.front(), (PxU32)shapes.size());

	for (unsigned int i = 0; i < shapes.size(); ++i)
	{
		*((UserData*)shapes[i]->userData)->color = actor_colour[i];
	}
}


PxRigidDynamic* JN_Scene::GetSelectedActor()
{
	return selected_actor;
}

void JN_Scene::SelectNextActor()
{
	std::vector<PxRigidDynamic*> actors(physics_scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC));

	if (actors.size() && (physics_scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, (PxActor * *)& actors.front(), (PxU32)actors.size())))
	{
		if (selected_actor)
		{
			for (unsigned int i = 0; i < actors.size(); i++)
				if (selected_actor == actors[i])
				{
					UnHighlightActor(selected_actor);

					// Select the next actor
					selected_actor = actors[(i + 1) % actors.size()];

					break;
				}
		}
		else
		{
			selected_actor = actors[0];
		}

		HighlightActor(selected_actor);
	}
	else
		selected_actor = 0;
}

std::vector<PxActor*> JN_Scene::GetAllActors()
{
	physx::PxActorTypeFlags selection_flag = PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eCLOTH;

	std::vector<PxActor*> actors(physics_scene->getNbActors(selection_flag));

	physics_scene->getActors(selection_flag, (PxActor * *)& actors.front(), (PxU32)actors.size());

	return actors;
}
