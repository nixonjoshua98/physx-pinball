#pragma once

#include <string>
#include <vector>

#include "PxPhysicsAPI.h"

using namespace physx;


class JN_ObjectLoader
{
public:
	JN_ObjectLoader(std::string file);
	~JN_ObjectLoader();

	std::vector<PxVec3> vertices;
	std::vector<PxU32> indices;

private:
	void Load(std::string file);

	std::vector<std::string> PerformRegex(std::string line, std::string regex, bool popFront);
};

