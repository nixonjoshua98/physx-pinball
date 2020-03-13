#include "JN_Paddle.h"

#include "JN_FilterGroup.h"

using namespace Actors;

JN_Paddle::JN_Paddle(const PxTransform& pose, PxVec2 dimensions,  PxReal offset, PxReal density) : Capsule(pose, dimensions, density), joint(0)
{
	PxTransform rotation = PxTransform({ 0.7071067811865476f, 0.7071067811865476f, 0, 0 });

	PxTransform first_pose = pose						* rotation;
	PxTransform second_pose	= PxTransform({ offset, 0, 0 }) * rotation;

	joint = new RevoluteJoint(nullptr, first_pose, this, second_pose);

	Name("Paddle");

	SetupFiltering(JN_FilterGroup::PADDLES, JN_FilterGroup::BALLS);

	joint->SetLimits(-0.5f, 0.5f);
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
