#pragma once

#include "PhysicsEngine.h"

#include "JN_BasicActors.h"

using namespace PhysicsEngine;


class JN_Cloth : public Actors::Actor
{
	PxClothMeshDesc mesh_desc;

public:
	JN_Cloth(PxTransform pose = PxTransform(PxIdentity), const PxVec2& size = PxVec2(1.f, 1.f), PxU32 width = 1, PxU32 height = 1, bool fix_top = true);

	~JN_Cloth();
};