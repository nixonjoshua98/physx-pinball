#include "JN_PinballFrame.h"

#include "JN_Functions.h"



JN_PinballFrame::JN_PinballFrame() : model(0)
{
	Create();
}

void JN_PinballFrame::Create()
{
	model = new JN_Model("PinballFrame.obj");

	model->Color(Helpers::RGB(255, 203, 136), 0);
	model->Color(Helpers::RGB(000, 203, 136), 1);
	model->Color(Helpers::RGB(255, 203, 136), 2);
	model->Color(Helpers::RGB(255, 203, 136), 3);

	model->Get()->is<PxRigidActor>()->setGlobalPose(PxTransform({ 0, 5, 0 }));
}

void JN_PinballFrame::AddToScene(JN_Scene* scene)
{
	scene->Add(model);
}
