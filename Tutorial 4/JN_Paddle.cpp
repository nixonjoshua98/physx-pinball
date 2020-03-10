#include "JN_Paddle.h"

#include "JN_FilterGroup.h"

using namespace Actors;

JN_Paddle::JN_Paddle(const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density), joint(0)
{
	PxTransform second_pose = pose;

	second_pose.p.x += 2.0f;

	joint = new RevoluteJoint(nullptr, pose, this, second_pose);

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
