
#include <iostream>

#include "JN_PinballScene.h"
#include "JN_PinballFrame.h"
#include "JN_Hexagon.h"
#include "JN_Functions.h"
#include "JN_Spinner.h"

#include "JN_Model.h"


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
	Actors::Sphere* ball = new Actors::Sphere({ 4.25f, 5.25f, 5.0f }, 0.20f);

	ball->Color({ 1, 0, 0 });
	ball->Material(ballMaterial);

	Add(ball);
}

void JN_PinballScene::CreateFrame()
{
	JN_PinballFrame* frame = new JN_PinballFrame();

	frame->AddToScene(this);
}

void JN_PinballScene::CreateHexagons()
{
	JN_Hexagon* leftTop  = new JN_Hexagon({ -3.5f, 5.75f, -5.0f }, 0.5f);
	JN_Hexagon* rightTop = new JN_Hexagon({ 2.50f, 5.75f, -5.0f }, 0.5f);

	JN_Hexagon* leftBtm  = new JN_Hexagon({ -3.5f, 5.75f, 5.0f }, 0.5f);
	JN_Hexagon* rightBtm = new JN_Hexagon({ 2.50f, 5.75f, 5.0f }, 0.5f);

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

void JN_PinballScene::CreateSpinner()
{
	JN_Spinner* spinner = new JN_Spinner({ -0.5f, 5.75f, 0.f }, { 1.5f, 0.25f, 0.125f });

	spinner->AddToScene(this);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	// Materials
	ballMaterial = GetPhysics()->createMaterial(0.0f, 0.15f, 0.0f);

	// Objects
	CreatePlane();
	CreateFrame();
	CreateSpinner();
	CreateHexagons();
	CreatePlunger();
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
		plunger->Activate(-15.0f);
		break;

	}
}

void JN_PinballScene::OnKeyReleased(int key)
{
	switch (key)
	{

	}
}
