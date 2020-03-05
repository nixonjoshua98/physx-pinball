#include "JN_PinballFrame.h"

#include "JN_Functions.h"



JN_PinballFrame::JN_PinballFrame() : model(0)
{
	Create();
}

void JN_PinballFrame::Create()
{
	model = new JN_Model("PinballFrame.obj");

	model->Color(Helpers::RGB(155, 203, 136), 0);	// Corner
	model->Color(Helpers::RGB(000, 203, 136), 1);	// Floor
	model->Color(Helpers::RGB(155, 203, 136), 2);	// Corner
	model->Color(Helpers::RGB(255, 203, 136), 3);	// Frame

	model->Get()->is<PxRigidActor>()->setGlobalPose(PxTransform({ 0, 5, 0 }));

	PxMaterial* cornerMaterial = CreateMaterial(0.0f, 0.0f, 2.5f);

	model->Material(cornerMaterial, 0);
	model->Material(cornerMaterial, 2);
}

void JN_PinballFrame::AddToScene(JN_Scene* scene)
{
	scene->Add(model);
}
