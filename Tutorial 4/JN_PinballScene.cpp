
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

	// Initialise and set the customised event callback
	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	plane = new Actors::Plane();
	plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
	Add(plane);

	cloth = new Cloth(PxTransform(PxVec3(-4.f, 9.f, 0.f)), PxVec2(8.f, 8.f), 40, 40);
	cloth->Color(color_palette[2]);
	Add(cloth);

	Actors::Box* b = nullptr;

	float x = -10.0f;
	float z = -10.0f;

	for (int i = 0; i < 5; ++i)
	{
		x = -5.0f;

		for (int j = 0; j < 5; ++j)
		{
			x += 0.9f;

			b = new Actors::Box({ x, 5.0f, z});

			b->Color(color_palette[3]);

			Add(b);
		}

		z += 1.0f;
	}

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
