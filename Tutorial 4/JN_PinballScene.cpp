
#include <iostream>

#include "JN_PinballScene.h"
#include "JN_PinballFrame.h"
#include "JN_Hexagon.h"


using namespace Actors;



JN_PinballScene::JN_PinballScene(): plunger(0), my_callback(0), frame(0), ballMaterial(0)
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
	Actors::Sphere* ball = new Actors::Sphere({ 7.25f, 5.25f, 5.0f }, 0.20f);

	ball->Color({ 1, 0, 0 });
	ball->Material(ballMaterial);

	Add(ball);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	// Materials
	ballMaterial = GetPhysics()->createMaterial(0.0f, 0.1f, 0.0f);

	// Objects
	CreatePlane();

	JN_PinballFrame* frame	= new JN_PinballFrame();
	plunger					= new JN_Plunger({ 7.25f, 5.5f, 18 });

	JN_Hexagon* hex1		= new JN_Hexagon({   3.5f, 5.75f, -10.0f }, 0.5f, 2.0f);
	JN_Hexagon* hex2		= new JN_Hexagon({  -4.5f, 5.75f, -10.0f }, 0.5f, 2.0f);
	JN_Hexagon* hex3		= new JN_Hexagon({   3.5f, 5.75f,   5.0f }, 0.5f, 2.0f);
	JN_Hexagon* hex4		= new JN_Hexagon({  -4.5f, 5.75f,   5.0f }, 0.5f, 2.0f);

	CreateBall();

	frame->AddToScene(this);
	plunger->AddToScene(this);

	hex1->AddToScene(this);
	hex2->AddToScene(this);
	hex3->AddToScene(this);
	hex4->AddToScene(this);
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
