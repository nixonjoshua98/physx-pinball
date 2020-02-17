
#include <iostream>

#include "JN_PinballScene.h"

using namespace Actors;



JN_PinballScene::JN_PinballScene(): plunger(0), my_callback(0)
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

void JN_PinballScene::CreateFrame()
{
	std::vector<Actors::StaticBox*> boxes = {
		new StaticBox({ FRAME_WIDTH, 0.25f, 0.25f }, { 0.25f, 0.25f, FRAME_LENGTH + 0.25f}), // Right
		new StaticBox({ -FRAME_WIDTH, 0.25f, 0.0f }, { 0.25f, 0.25f, FRAME_LENGTH }), // Left

		new StaticBox({ -0.5f, 0.25f, +FRAME_LENGTH + 0.25f }, { FRAME_WIDTH - 0.25f, 0.25f, 0.25f }), // Bottom
		new StaticBox({ +0.0f, 0.25f, -FRAME_LENGTH - 0.25f }, { FRAME_WIDTH + 0.25f, 0.25f, 0.25f }), // Top

		// Plunger Pipe
		new StaticBox({ 7.0f, 0.25f, 5.f }, { 0.25f, 0.25f, 10.0f })
	};

	for (auto b : boxes)
	{
		b->Color({ 0, 1, 0 });

		Add(b);
	}
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

void JN_PinballScene::AddObjects()
{
	plunger = new JN_Plunger(this);
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	GetMaterial()->setDynamicFriction(.2f);

	my_callback = new MySimulationEventCallback();

	physics_scene->setSimulationEventCallback(my_callback);

	CreatePlane();
	CreateFrame();
	CreateBall();

	AddObjects();
}

void JN_PinballScene::CustomUpdate(PxReal delta)
{

}

void JN_PinballScene::OnKeyPressed(int key)
{
	std::cout << key << std::endl;

	switch (key)
	{
		// Space
	case 32:
		plunger->Activate(-125.0f);
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
