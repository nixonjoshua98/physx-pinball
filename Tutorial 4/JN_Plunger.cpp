
#include "PxPhysicsAPI.h"

#include "JN_Plunger.h"
#include "JN_BasicActors.h"
#include "JN_Functions.h"

#include "PhysicsEngine.h"

using namespace PhysicsEngine;

JN_Plunger::JN_Plunger(PxTransform pose)
{
	box = new Box(pose, { 0.25f, 0.25f, 4 });

	joint = PxD6JointCreate(*GetPhysics(), NULL, pose, (PxRigidActor*)box->Get(), PxTransform(PxVec3(0.f, 0.f, 0.f)));

	// Some magic attributes I used trial and error to get
	joint->setMotion(PxD6Axis::eZ, PxD6Motion::eLIMITED);
	joint->setDrive(PxD6Drive::eZ, PxD6JointDrive(100.f, 25.f, PX_MAX_F32, false));

	box->Color(Helpers::RGB(255, 191, 70));
}

void JN_Plunger::Activate(PxReal force)
{
	box->AddForce({ 0, 0, force });
}

void JN_Plunger::AddToScene(JN_Scene* scene)
{
	scene->Add(box);
}
