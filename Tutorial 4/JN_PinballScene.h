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


class JN_PinballScene : public JN_Scene
{
public:
	JN_PinballScene();

	const float FRAME_LENGTH	= 15.0f;
	const float FRAME_WIDTH		= 8.0f;

	void SetVisualisation();

	int balls_left = 3;

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
	
	VisualDebugger::HUD HUD;

	JN_Paddle* paddles[2];

	void CreatePlane();
	void CreateBall();
	void CreateFrame();
	void CreatePaddles();
	void CreateHexagons();
	void CreatePlunger();
	void CreateSpinners();

	void UpdateHUD();

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

