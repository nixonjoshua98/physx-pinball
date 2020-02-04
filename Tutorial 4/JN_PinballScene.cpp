
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

void JN_PinballScene::CreateFrame()
{
	const float LENGTH = 15.0f;
	const float WIDTH = 8.0f;

	std::vector<Actors::StaticBox*> boxes = {
		new Actors::StaticBox({ WIDTH, 0.5f, 0.0f }, { 0.5f, 0.5f, LENGTH }), // Left
		new Actors::StaticBox({ -WIDTH, 0.5f, 0.0f }, { 0.5f, 0.5f, LENGTH }), // Right

		new Actors::StaticBox({ 0.0f, 0.5f, LENGTH + 0.5f}, {WIDTH + 0.5f, 0.5f, 0.5f }), // Bottom
		new Actors::StaticBox({ 0.0f, 0.5f, -LENGTH - 0.5f }, { WIDTH + 0.5f, 0.5f, 0.5f }), // Top
	};

	for (auto b : boxes)
	{
		b->Color(PxVec3(55.f / 255.f, 55.f / 255.f, 55.f / 255.f));

		Add(b);
	}
}

void JN_PinballScene::CreatePaddles()
{
	paddle = new JN_Paddle();

	Add(paddle->GetActor());
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	GetMaterial()->setDynamicFriction(.2f);

	// Initialise and set the customised event callback
	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	Actors::Plane* plane = new Actors::Plane();
	plane->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
	Add(plane);

	CreateFrame();
	CreatePaddles();

	Add(new Actors::Sphere({ 0.0f, 0.5f, 0.0f }, 0.25f));
}

void JN_PinballScene::CustomUpdate(PxReal delta)
{

}

void JN_PinballScene::OnKeyPressed(char key)
{
	switch (key)
	{
	case 'H':
		paddle->Activate();
		break;
	}
}

void JN_PinballScene::OnKeyReleased(char key)
{
	switch (key)
	{

	}
}
