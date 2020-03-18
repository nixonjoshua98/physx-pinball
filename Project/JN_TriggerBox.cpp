#include "JN_TriggerBox.h"

namespace Actors
{
	using namespace physx;

	JN_TriggerBox::JN_TriggerBox(const std::string& name, const PxTransform& pose, PxVec3 dimensions, PxReal density) : Box(pose, dimensions, density)
	{
		Name(name);

		SetTrigger(true);

		// Stop the trigger from moving
		SetKinematic(true);

		// Disables the object from being rendered
		GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
	}

	// Adds the object to the scene
	void JN_TriggerBox::AddToScene(JN_Scene* scene)
	{
		scene->Add(this);
	}
}
