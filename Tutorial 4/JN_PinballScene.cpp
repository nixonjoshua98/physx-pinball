
#include <iostream>

#include "JN_PinballScene.h"
#include "JN_Model.h"


using namespace Actors;



JN_PinballScene::JN_PinballScene(): plunger(0), my_callback(0), frame(0)
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

	// Joints
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
}

void JN_PinballScene::CreatePlane()
{
	Plane* plane = new Actors::Plane();

	plane->Color({ 210.f / 255.f, 210.f / 255.f, 210.f / 255.f });

	Add(plane);
}

void JN_PinballScene::CreateBall()
{
	Actors::Sphere* ball = new Actors::Sphere({ 7.f, 0.25f, 12.f }, 0.25f);

	ball->Color({ 1, 0, 0 });

	Add(ball);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	GetMaterial()->setDynamicFriction(.1f);

	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);


	// - - Objects - - 

	CreatePlane();

	// Pinball Frame
	JN_Model* frame = new JN_Model("PinballFrame.obj");

	frame->AddToScene(this);

	frame->Color({ 139.0f / 255.0f, 69.0f / 255.0f, 19.0f / 255.0f});

	// Plunger
	plunger = new JN_Plunger({ 7.25f, 0.5f, 18 });

	plunger->AddToScene(this);

	CreateBall();
}

void JN_PinballScene::CustomUpdate(PxReal delta)
{

}

void JN_PinballScene::OnKeyPressed(int key)
{
	// std::cout << key << std::endl;

	switch (key)
	{
		// Space
	case 32:
		plunger->Activate(-75.0f);
		break;

		// F
	case 70:
		break;
	}
}

void JN_PinballScene::OnKeyReleased(int key)
{
	switch (key)
	{

	}
}
