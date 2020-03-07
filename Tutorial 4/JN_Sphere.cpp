
#include "JN_BasicActors.h"
#include "JN_Sphere.h"


namespace Actors
{
	JN_Sphere::JN_Sphere(const PxTransform& pose, PxReal radius, PxReal density) : DynamicActor(pose)
	{
		CreateShape(PxSphereGeometry(radius), density);
	}
}