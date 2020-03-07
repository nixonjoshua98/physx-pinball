#include "JN_TriggerBox.h"

namespace Actors
{
	using namespace physx;

	JN_TriggerBox::JN_TriggerBox(const std::string& name, const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density)
	{
		Name(name);

		SetTrigger(true);
		SetKinematic(true);

		GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
	}

	void JN_TriggerBox::AddToScene(JN_Scene* scene)
	{
		scene->Add(this);
	}
}
