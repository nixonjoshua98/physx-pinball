#include "JN_Spinner.h"
#include "JN_Functions.h"
#include "JN_FilterGroup.h"

namespace Actors
{
	JN_Spinner::JN_Spinner(const PxTransform& pose, PxVec3 dimensions, PxReal density, PxReal velocity) : Box(pose, dimensions, density)
	{
		this->velocity = velocity;

		// Set the colour
		Color(Helpers::RGB(220, 220, 220));

		// Rotate the box
		PxQuat q = PxQuat(0.0f, 0.0f, 0.7071067811865476f, 0.7071067811865476f);

		// Joint
		joint = new RevoluteJoint(nullptr, pose * PxTransform(q), this, PxTransform(PxVec3(PxIdentity), q));

		Name("Spinner");

		// Setup the collision groups
		SetupFiltering(JN_FilterGroup::SPINNERS, JN_FilterGroup::BALLS);
	}

	// Add the box to the scene
	void JN_Spinner::AddToScene(JN_Scene* scene)
	{
		scene->Add(this);

		// Spin the box (can only be called after being added to the scene)
		joint->DriveVelocity(velocity);
	}
}
