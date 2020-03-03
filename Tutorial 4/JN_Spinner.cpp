#include "JN_Spinner.h"
#include "JN_Functions.h"

namespace Actors
{
	JN_Spinner::JN_Spinner(const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density)
	{
		SetKinematic(true);

		Color(Helpers::RGB(0, 0, 0));

		// Revolute Joint
	}

	JN_Spinner::~JN_Spinner()
	{

	}

	void JN_Spinner::AddToScene(JN_Scene* scene)
	{
		scene->Add(this);
	}
}
