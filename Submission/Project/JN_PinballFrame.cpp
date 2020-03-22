#include "JN_PinballFrame.h"

#include "JN_Functions.h"



JN_PinballFrame::JN_PinballFrame() : JN_Model("PinballFrame.obj")
{
	// Set colour of each shape
	Color(Helpers::RGB(155, 203, 136), 0);	// Corner
	Color(Helpers::RGB(000, 203, 136), 1);	// Floor
	Color(Helpers::RGB(155, 203, 136), 2);	// Corner
	Color(Helpers::RGB(255, 203, 136), 3);	// Frame

	GetShape(4)->setFlag(PxShapeFlag::eVISUALIZATION, false);

	// Set position
	Get()->is<PxRigidActor>()->setGlobalPose(PxTransform({ 0, 5, 0 }));

	PxMaterial* cornerMaterial = CreateMaterial(0.0f, 0.0f, 1.0f);
	PxMaterial* frameMaterial = CreateMaterial(0.0f, 0.0f, 0.5f);

	Material(frameMaterial, 3);

	Material(cornerMaterial, 0);
	Material(cornerMaterial, 2);
}

void JN_PinballFrame::AddToScene(JN_Scene* scene)
{
	scene->Add(this);
}
