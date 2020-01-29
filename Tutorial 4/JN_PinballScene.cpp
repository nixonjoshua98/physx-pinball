
#include <iostream>

#include "JN_PinballScene.h"


JN_PinballScene::JN_PinballScene()
{

}

void JN_PinballScene::SetVisualisation()
{
	// Other general stuff
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	// Cloth visualisation
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_HORIZONTAL, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_VERTICAL, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_BENDING, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eCLOTH_SHEARING, 1.0f);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	GetMaterial()->setDynamicFriction(.2f);

	///Initialise and set the customised event callback
	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	plane = new Plane();
	plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
	Add(plane);

	cloth = new Cloth(PxTransform(PxVec3(-4.f, 9.f, 0.f)), PxVec2(8.f, 8.f), 40, 40);
	cloth->Color(color_palette[2]);
	Add(cloth);

	box = new Box(PxTransform(PxVec3(0.f, 2.f, 0.f)), PxVec3(2.f, 2.f, 2.f));
	box->Color(color_palette[3]);
	Add(box);

	Box* b = new Box(PxTransform(PxVec3(0.f, 50.f, 0.f)), PxVec3(2.f, 2.f, 2.f));
	b->Color(color_palette[3]);
	Add(b);

	// Setting custom cloth parameters
	((PxCloth*)cloth->Get())->setStretchConfig(PxClothFabricPhaseType::eBENDING, PxClothStretchConfig(1.f));
}

void JN_PinballScene::CustomUpdate()
{

}

void JN_PinballScene::OnKeyPressed(char key)
{
	std::cout << key << " pressed\n";
}

void JN_PinballScene::OnKeyReleased(char key)
{
	std::cout << key << " released\n";
}
