#include "JN_ObjectLoader.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>


JN_ObjectLoader::JN_ObjectLoader(std::string file)
{
	vertices = std::vector<PxVec3>();
	indices = std::vector<PxU32>();

	Load(file);
}

JN_ObjectLoader::~JN_ObjectLoader()
{

}

void JN_ObjectLoader::Load(std::string file)
{
	std::string line;

	std::ifstream stream(file);

	if (stream.is_open())
	{
		std::cout << "Opened: " << file << std::endl;

		// Iterate through the file line by line
		while (std::getline(stream, line))
		{
			if (line.rfind("vt", 0) == 0)
				continue;

			else if (line.rfind("vn", 0) == 0)
				continue;

			else if (line.rfind("v", 0) == 0)
			{
				std::vector<std::string> results = PerformRegex(line, "\\s+", true);

				for (unsigned int i = 0; i < results.size(); i += 3)
				{
					PxVec3 vec = PxVec3({ std::stof(results[i]), std::stof(results[i + 1]), std::stof(results[i + 2]) });

					vertices.push_back(vec);

					std::cout << "X: " << vec.x << " " << "Y: " << vec.y << " " << "Z: " << vec.z << std::endl;
				}
			}

			else if (line.rfind("f", 0) == 0)
			{
				std::replace(line.begin(), line.end(), '/', ' ');

				std::vector<std::string> results = PerformRegex(line, "\\s+", true);

				for (unsigned int i = 0; i < results.size(); i += 3)
				{
					indices.push_back(std::stoi(results[i]) - 1);
				}
			}
		}
	}

	else
	{
		std::cout << "Failed to open: " << file << std::endl;
	}
}

std::vector<std::string> JN_ObjectLoader::PerformRegex(std::string line, std::string regex, bool popFront)
{
	std::regex re(regex);

	std::vector<std::string> result
	{
		std::sregex_token_iterator(line.begin(), line.end(), re, -1), {}
	};

	if (popFront)
		result.erase(result.begin());

	return result;
}
