#include "PxPhysicsAPI.h"

#include "JN_Trampoline.h"



JN_Trampoline::JN_Trampoline(const PxTransform& pose, const PxVec3& dimensions, PxReal stiffness, PxReal damping)
{
	// Thickness of the boxes
	PxReal thickness = 0.1f;

	bottom = new Box(
		PxTransform(PxVec3(pose.p.x, pose.p.y + dimensions.y + thickness, pose.p.z), pose.q),
		PxVec3(dimensions.x, thickness, dimensions.z), 0.25f);

	top	= new Box(
		PxTransform(PxVec3(pose.p.x, pose.p.y + dimensions.y + thickness, pose.p.z - (thickness * 2.0f)), pose.q),
		PxVec3(dimensions.x, thickness, dimensions.z), 0.25f);

	springs.resize(4);

	// Adds a spring in each corner of the trampoline?

	springs[0] = new DistanceJoint(
		bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), 
		top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));

	springs[1] = new DistanceJoint(
		bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)),
		top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));

	springs[2] = new DistanceJoint(
		bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)),
		top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));

	springs[3] = new DistanceJoint(
		bottom,PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)),
		top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));

	for (unsigned int i = 0; i < springs.size(); i++)
	{
		springs[i]->Stiffness(stiffness);
		springs[i]->Damping(damping);
	}
}


JN_Trampoline::~JN_Trampoline()
{
	// Delete all spring objects
	for (unsigned int i = 0; i < springs.size(); i++)
		delete springs[i];
}

void JN_Trampoline::AddToScene(JN_Scene* scene)
{
	scene->Add(bottom);
	scene->Add(top);
}

void JN_Trampoline::AddForce(PxReal force)
{
	// Sets kinematic so the bottom doesn't move (I did this while I used this as the plunger)
	bottom->SetKinematic(true);

	top->Get()->is<PxRigidDynamic>()->addForce({ 0, 0, force });
}
