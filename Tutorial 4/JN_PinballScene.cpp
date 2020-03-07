
#include <iostream>

#include "JN_PinballScene.h"
#include "JN_PinballFrame.h"
#include "JN_Hexagon.h"
#include "JN_Functions.h"
#include "JN_Spinner.h"
#include "JN_Model.h"
#include "JN_Sphere.h"


using namespace Actors;



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

	// Joints
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
	physics_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
}

void JN_PinballScene::CreatePlane()
{
	Plane* plane = new Plane();

	plane->Color({ 210.f / 255.f, 210.f / 255.f, 210.f / 255.f });

	Add(plane);
}

void JN_PinballScene::CreateBall()
{
	JN_Sphere* ball = new JN_Sphere({ -3.0f, 5.25f, 3.0f }, 0.2f, 3.0f);

	ball->Color({ 1, 0, 0 });
	ball->Material(ballMaterial);

	Add(ball);
}

void JN_PinballScene::CreateFrame()
{
	JN_PinballFrame* frame = new JN_PinballFrame();

	frame->AddToScene(this);
}

void JN_PinballScene::CreatePaddles()
{
	// Rotated by 22 degrees
	paddles[0] = new JN_Paddle(PxTransform({ -1.85f, 5.5f, 8.9f }, { 0.981627183447664, 0, 00.1908089953765448, 0 }), { 1.0f, 0.25f, 0.125f });
	paddles[1] = new JN_Paddle(PxTransform({ 00.85f, 5.5f, 8.9f }, { 0.981627183447664, 0, -0.1908089953765448, 0 }), { 1.0f, 0.25f, 0.125f });

	paddles[0]->AddToScene(this);
	paddles[1]->AddToScene(this);
}

void JN_PinballScene::CreateHexagons()
{
	JN_Hexagon* leftTop = new JN_Hexagon({ -3.5f, 5.5f, -5.0f });
	JN_Hexagon* rightTop = new JN_Hexagon({ 2.50f, 5.5f, -5.0f });

	JN_Hexagon* leftBtm  = new JN_Hexagon({ -3.5f, 5.5f, 5.0f });
	JN_Hexagon* rightBtm = new JN_Hexagon({ 2.50f, 5.5f, 5.0f });

	leftTop->AddToScene(this);
	leftBtm->AddToScene(this);

	rightTop->AddToScene(this);
	rightBtm->AddToScene(this);
}

void JN_PinballScene::CreatePlunger()
{
	plunger = new JN_Plunger({ 4.25f, 5.5f, 11 });

	plunger->AddToScene(this);
}

void JN_PinballScene::CreateSpinners()
{
	JN_Spinner* left = new JN_Spinner({ -1.5f, 5.5f, 0.f }, { 1.25f, 0.25f, 0.125f });
	JN_Spinner* right = new JN_Spinner({ 1.0f, 5.5f, 0.f }, { 1.25f, 0.25f, 0.125f });

	left->AddToScene(this);
	right->AddToScene(this);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	simulation_callback = new JN_SimulationCallback();

	physics_scene->setSimulationEventCallback(simulation_callback);

	// Materials
	ballMaterial = GetPhysics()->createMaterial(0.0f, 0.15f, 0.0f);

	// Objects
	CreatePlane();
	CreateFrame();
	CreateSpinners();
	CreateHexagons();
	CreatePlunger();
	CreatePaddles();
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
		plunger->Activate(-20.0f);
		break;

		// R
	case 82:
		paddles[0]->Activate(5.0f);
		break;

		// T
	case 84:
		paddles[1]->Activate(5.0f);
		break;
	}
}

void JN_PinballScene::OnKeyReleased(int key)
{
	switch (key)
	{

	}
}
