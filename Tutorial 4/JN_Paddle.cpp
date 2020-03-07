#include "JN_Paddle.h"

#include "JN_FilterGroup.h"

using namespace Actors;

JN_Paddle::JN_Paddle(const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density), joint(0)
{
	joint = new RevoluteJoint(nullptr, pose, this, PxTransform(PxVec3(PxIdentity)));

	//joint->SetLimits(-0.5f, 0.5f);

	Name("Paddle");

	SetupFiltering(JN_FilterGroup::PADDLES, JN_FilterGroup::BALLS);
}

JN_Paddle::~JN_Paddle()
{

}

void JN_Paddle::AddToScene(JN_Scene* scene)
{
	scene->Add(this);
}

void Actors::JN_Paddle::Activate(PxReal force)
{
	joint->DriveVelocity(force);
}
