#pragma once

#include "BasicActors.h"
#include "JN_Scene.h"

#include <string>

using namespace PhysicsEngine;

class JN_Model
{
public:
	JN_Model(std::string file, PxTransform pose = PxTransform(PxIdentity));

	void AddToScene(JN_Scene* scene);

	void Color(PxVec3, PxU32 = 4294967295U);

private:
	TriangleMesh* mesh;
};

