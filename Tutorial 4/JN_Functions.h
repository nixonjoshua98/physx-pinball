#ifndef __JN_FUNCTIONS__

#include "PxPhysicsAPI.h"

#define __JN_FUNCTIONS__

namespace Helpers
{
	using namespace physx;

	inline PxVec3 RGB(float r, float g, float b)
	{
		return PxVec3(r, g, b) / 255.0f;
	}
}

#endif // !__JN_FUNCTIONS__