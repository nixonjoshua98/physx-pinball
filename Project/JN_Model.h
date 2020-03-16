#pragma once

#include "JN_BasicActors.h"
#include "JN_Scene.h"

#include <string>

using namespace Actors;
using namespace PhysicsEngine;

class JN_Model : public StaticActor
{
public:
	JN_Model(std::string file, PxTransform pose = PxTransform(PxIdentity));

	PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc);
};

