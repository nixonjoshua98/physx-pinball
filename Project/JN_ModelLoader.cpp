#include "JN_ModelLoader.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>


JN_ModelLoader::JN_ModelLoader(std::string file)
{
	vertices = std::vector<PxVec3>();

	Load(file);
}

JN_ModelLoader::~JN_ModelLoader()
{

}

void JN_ModelLoader::Load(std::string file)
{
	std::string line;

	std::ifstream stream(file);

	int objectID = -1;

	if (stream.is_open())
	{
		std::cout << "Opened: " << file << std::endl;

		// Iterate through the file line by line
		while (std::getline(stream, line))
		{
			// New object
			if (line[0] == 'o')
			{
				++objectID;

				indicesVector[objectID] = std::vector<PxU32>();
			}

			else if (line.rfind("vt", 0) == 0)
				continue;

			else if (line.rfind("vn", 0) == 0)
				continue;

			// Vertices
			else if (line[0] == 'v')
			{
				std::vector<std::string> results = PerformRegex(line, "\\s+", true);

				vertices.push_back({ std::stof(results[0]), std::stof(results[1]), std::stof(results[2]) });
			}

			// Faces (Indices)
			else if (line.rfind("f", 0) == 0)
			{
				std::replace(line.begin(), line.end(), '/', ' ');

				std::vector<std::string> results = PerformRegex(line, "\\s+", true);

				for (unsigned int i = 0; i < results.size(); i += 3)
				{
					// Obj starts at 1 so we need to -1 to it
					indicesVector[objectID].push_back(std::stoi(results[i]) - 1);
				}

				std::cout << std::endl;
			}
		}
	}

	else
	{
		std::cout << "Failed to open: " << file << std::endl;
	}
}

// Perform regex string on a string
std::vector<std::string> JN_ModelLoader::PerformRegex(std::string line, std::string regex, bool popFront)
{
	std::regex re(regex);

	// Perform the regex expression
	std::vector<std::string> result
	{
		std::sregex_token_iterator(line.begin(), line.end(), re, -1), {}
	};

	// Remove the first element is needed
	if (popFront)
		result.erase(result.begin());

	return result;
}
