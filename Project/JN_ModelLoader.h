#pragma once

#include <string>
#include <map>
#include <vector>

#include "PxPhysicsAPI.h"

using namespace physx;


class JN_ModelLoader
{
public:
	JN_ModelLoader(std::string file);
	~JN_ModelLoader();

	std::vector<PxVec3> vertices;

	// Store the indices for each object
	std::map<int, std::vector<PxU32>> indicesVector;

private:
	void Load(std::string file);

	// Perform regular expression on string
	std::vector<std::string> PerformRegex(std::string line, std::string regex, bool popFront);
};

