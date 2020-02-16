

#include <vector>

#include "BasicActors.h"
#include "JN_Scene.h"
#include "JN_BasicActors.h"

using namespace PhysicsEngine;
using namespace physx;
using namespace Actors;



class JN_Trampoline
{
	std::vector<DistanceJoint*> springs;

	Box* top;
	Box* bottom;

public:
	JN_Trampoline(const PxTransform& pose = PxTransform(PxIdentity), const PxVec3& dimensions = PxVec3(1.f, 1.f, 1.f), PxReal stiffness = 1.f, PxReal damping = 1.f);
	~JN_Trampoline();

	void AddToScene(JN_Scene* scene);
	void AddForce(PxReal force);
};