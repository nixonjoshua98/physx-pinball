
#include <iostream>

#include "JN_PinballScene.h"
#include "JN_PinballFrame.h"
#include "JN_Hexagon.h"
#include "JN_Functions.h"
#include "JN_Spinner.h"
#include "JN_Model.h"

#include "JN_TriggerBox.h"


using namespace Actors;

const int SIMULATION = 0;



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
	ball = new JN_Sphere({ 4.25f, 5.25f, 8.0f }, 0.2f, 3.0f);

	ball->Color({ 1, 0, 0 });
	ball->Material(ballMaterial);

	Add(ball);
}

void JN_PinballScene::CreateFrame()
{
	JN_PinballFrame* frame = new JN_PinballFrame();

	JN_TriggerBox* deathBox = new JN_TriggerBox("DeathTrigger", PxTransform({ -0.5f, 5.5f, 11.4f }), { 4.0f, 0.25f, 0.1f });

	frame->AddToScene(this);
	deathBox->AddToScene(this);
}

void JN_PinballScene::CreatePaddles()
{
	paddles[0] = new JN_Paddle(PxTransform({ -2.5f, 5.5f, 8.8f }), { 0.25f, 0.5f }, -0.5f);
	paddles[1] = new JN_Paddle(PxTransform({ 1.5f, 5.5f, 8.8f }), { 0.25f, 0.5f }, 0.5f);

	paddles[0]->AddToScene(this);
	paddles[1]->AddToScene(this);
}

void JN_PinballScene::CreateHexagons()
{
	std::vector<PxVec3> positions {
		{ -0.5f, 5.5f, -5.0f },
		{ -3.5f, 5.5f, -3.0f },
		{ 2.50f, 5.5f, -3.0f },
		{ 2.50f, 5.5f, +5.0f },
		{ -3.5f, 5.5f, +5.0f },
	};

	for (PxVec3 v : positions)
	{
		JN_Hexagon* hex = new JN_Hexagon(PxTransform(v));

		hex->AddToScene(this);
	}
}

void JN_PinballScene::CreatePlunger()
{
	plunger = new JN_Plunger({ 4.25f, 5.5f, 11 });

	plunger->AddToScene(this);
}

void JN_PinballScene::CreateSpinners()
{
	JN_Spinner* spinner = new JN_Spinner({ -0.5f, 5.5f, 1.0f }, { 1.25f, 0.25f, 0.125f }, 1.0f, 1.f);

	spinner->AddToScene(this);
}

void JN_PinballScene::UpdateHUD()
{
	HUD.Clear();

	HUD.AddLine(SIMULATION, "");
	HUD.AddLine(SIMULATION, "");
	HUD.AddLine(SIMULATION, "F6   - Toggle Shadows");
	HUD.AddLine(SIMULATION, "F7   - Toggle Render Mode");
	HUD.AddLine(SIMULATION, "F8   - Reset Camera");
	HUD.AddLine(SIMULATION, "F10 - Pause Simulation");
	HUD.AddLine(SIMULATION, "");
	HUD.AddLine(SIMULATION, "Score:        " + std::to_string(totalScore));
	HUD.AddLine(SIMULATION, "Balls Left: " + std::to_string(ballsLeft));

	if (ballsLeft == 0)
	{
		HUD.AddLine(SIMULATION, " ");
		HUD.AddLine(SIMULATION, "GAME OVER");
		HUD.AddLine(SIMULATION, " ");
		HUD.AddLine(SIMULATION, "P - Restart");
	}

	HUD.ActiveScreen(SIMULATION);

	HUD.Color(Helpers::RGB(0, 0, 0));
}

void JN_PinballScene::CustomInit()
{
	SetVisualisation();

	simulation_callback = new JN_SimulationCallback();

	physics_scene->setSimulationEventCallback(simulation_callback);

	// Materials
	ballMaterial = GetPhysics()->createMaterial(0.0f, 0.15f, 0.0f);

	CreatePlane();
	CreateFrame();
	CreateSpinners();
	CreateHexagons();
	CreatePlunger();
	CreatePaddles();
	CreateBall();

	start = std::chrono::system_clock::now();

	// Interface
	UpdateHUD();
}

void JN_PinballScene::CustomUpdate(PxReal delta)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	int seconds = std::chrono::duration<float>(now - start).count();

	int timeScore = seconds * 10;

	totalScore = simulation_callback->score + timeScore;

	if (simulation_callback->dead_ball_trigger)
	{
		physics_scene->removeActor(*ball->Get());

		ballsLeft--;

		if (ballsLeft > 0)
			CreateBall();
	}
}

void JN_PinballScene::OnKeyPressed(int key)
{
	std::cout << key << std::endl;

	switch (key)
	{
		// Space
	case 32:
		plunger->Activate(-20.0f);
		break;

		// P
	case 80:
		if (ballsLeft == 0)
		{
			simulation_callback->score = 0;

			ballsLeft = 3;
			totalScore = 0;

			start = std::chrono::system_clock::now();

			CreateBall();
		}
		break;

		// R
	case 82:
		paddles[0]->Activate(10.0f);
		break;

		// T
	case 84:
		paddles[1]->Activate(-10.0f);
		break;
	}
}

void JN_PinballScene::OnKeyReleased(int key)
{
	switch (key)
	{
		// R
	case 82:
		paddles[0]->Activate(-10.0f);
		break;

		// T
	case 84:
		paddles[1]->Activate(10.0f);
		break;
	}
}

void JN_PinballScene::CustomRender()
{
	UpdateHUD();

	HUD.Render();
}
