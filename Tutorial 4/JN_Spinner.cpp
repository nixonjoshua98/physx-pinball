#include "JN_Spinner.h"
#include "JN_Functions.h"

namespace Actors
{
	JN_Spinner::JN_Spinner(const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density)
	{
		Color(Helpers::RGB(220, 220, 220));

		PxQuat q = PxQuat(0.0f, 0.0f, 0.7071067811865476f, 0.7071067811865476f);

		joint = new RevoluteJoint(nullptr, pose * PxTransform(q), this, PxTransform(PxVec3(PxIdentity), q));
	}

	JN_Spinner::~JN_Spinner()
	{

	}

	void JN_Spinner::AddToScene(JN_Scene* scene)
	{
		scene->Add(this);

		joint->DriveVelocity(-2.5f);
	}
}
