
#include <iostream>

#include "JN_PinballScene.h"


JN_PinballScene::JN_PinballScene() : my_callback(0), plane(0)
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

	std::vector<Actors::StaticBox*> boxes = {
		new Actors::StaticBox({ 5.0f, 0.5f, 0.0f }, { 0.5f, 0.5f, 10.f }),
		new Actors::StaticBox({ -5.0f, 0.5f, 0.0f }, { 0.5f, 0.5f, 10.f }),

		 new Actors::StaticBox({ 0.0f, 0.5f, 10.5f }, { 5.5f, 0.5f, 0.5f }),
		 new Actors::StaticBox({ 0.0f, 0.5f, -10.5f}, { 5.5f, 0.5f, 0.5f }),
	};

	for (auto b : boxes)
	{
		b->Color(PxVec3(55.f / 255.f, 55.f / 255.f, 55.f / 255.f));

		Add(b);
	}

	ball = new Actors::Sphere({ 0.0f, 0.5f, 0.0f }, 0.5f);

	ball->Color({ 0.0f, 0.0f, 0.0f });

	Add(ball);
}

void JN_PinballScene::CustomUpdate(PxReal delta)
{

}

void JN_PinballScene::OnKeyPressed(char key)
{
	switch (key)
	{
	case 'H':
		ball->AddForce({ 0.0f, 0.0f, 1.0f });
		break;
	}
}

void JN_PinballScene::OnKeyReleased(char key)
{
	std::cout << key << " released\n";
}
