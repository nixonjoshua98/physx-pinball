
#include <vector>

#include "JN_Scene.h"

#include <iostream>

void JN_Scene::Init()
{
#if PX_PHYSICS_VERSION < 0x304000
	throw new Exception("SDK version is less than 3.4");
#endif

	PxSceneDesc scene_desc(GetPhysics()->getTolerancesScale());
	
	// Set number of CPU threads
	if (!scene_desc.cpuDispatcher)
	{
		scene_desc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	}

	// Set shader
	scene_desc.filterShader = PxDefaultSimulationFilterShader;

	// Create the scene for the physics world from the description
	physics_scene = GetPhysics()->createScene(scene_desc);

	if (!physics_scene)
		throw new Exception("Physics scene failed to be created.");

	// Earth gravity: (0.0f, -9.81f, 0.0f)
	physics_scene->setGravity(PxVec3(0.0f, -9.81f, 0.0f));

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
