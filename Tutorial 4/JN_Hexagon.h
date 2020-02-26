#pragma once

#include "BasicActors.h"

#include "JN_Scene.h"

#include "PxPhysicsAPI.h"

using namespace physx;

class JN_Hexagon
{
public:
	JN_Hexagon(const PxTransform& pose = PxTransform(PxIdentity), PxReal height = 1.0f, PxReal radius = 1.0f);
	~JN_Hexagon();

	void AddToScene(JN_Scene* scene);

private:
	PhysicsEngine::ConvexMesh* convex;
};

