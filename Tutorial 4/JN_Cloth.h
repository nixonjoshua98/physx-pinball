#pragma once

#include "PhysicsEngine.h"

#include "JN_BasicActors.h"

using namespace PhysicsEngine;


class Jn_Cloth : public Actors::Actor
{
	PxClothMeshDesc mesh_desc;

public:
	Jn_Cloth(PxTransform pose = PxTransform(PxIdentity), const PxVec2& size = PxVec2(1.f, 1.f), PxU32 width = 1, PxU32 height = 1, bool fix_top = true);

	~Jn_Cloth();
};