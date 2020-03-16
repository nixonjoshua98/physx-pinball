
#include "JN_BasicActors.h"
#include "JN_Sphere.h"

#include "JN_FilterGroup.h"


namespace Actors
{
	JN_Sphere::JN_Sphere(const PxTransform& pose, PxReal radius, PxReal density) : DynamicActor(pose)
	{
		CreateShape(PxSphereGeometry(radius), density);

		Name("Ball");

		SetupFiltering(JN_FilterGroup::BALLS, JN_FilterGroup::HEXAGONS | JN_FilterGroup::SPINNERS | JN_FilterGroup::PADDLES);
	}
}