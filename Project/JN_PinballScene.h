#pragma once

#include "MyPhysicsEngine.h"

#include "Extras/HUD.h"

#include "JN_Scene.h"

#include "JN_BasicActors.h"
#include "JN_Plunger.h"
#include "JN_Paddle.h"
#include "JN_Model.h"
#include "JN_Sphere.h"

#include "JN_SimulationCallback.h"

#include <chrono>


class JN_PinballScene : public JN_Scene
{
public:
	JN_PinballScene();

	void SetVisualisation();

	int ballsLeft = 3;

	// Events
	void OnKeyPressed(int key);
	void OnKeyReleased(int key);

	void CustomRender() override;

private:
	JN_SimulationCallback* simulation_callback;

	PxMaterial* ballMaterial;

	JN_Sphere* ball;
	JN_Plunger* plunger;
	JN_Model* frame;

	std::chrono::system_clock::time_point start;

	int totalScore = 0;
	
	VisualDebugger::HUD HUD;

	JN_Paddle* paddles[2];

	// Object creation
	void CreatePlane();
	void CreateBall();
	void CreateFrame();
	void CreatePaddles();
	void CreateCloth();
	void CreateHexagons();
	void CreatePlunger();
	void CreateSpinners();

	void UpdateHUD();

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

