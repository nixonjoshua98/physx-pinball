#pragma once

#include "JN_Scene.h"

#include "MyPhysicsEngine.h"

#include "JN_BasicActors.h"
#include "JN_Plunger.h"


class JN_PinballScene : public JN_Scene
{
public:
	JN_PinballScene();

	const float FRAME_LENGTH	= 15.0f;
	const float FRAME_WIDTH		= 8.0f;

	void SetVisualisation();

	// Events
	void OnKeyPressed(int key);
	void OnKeyReleased(int key);

private:
	MySimulationEventCallback* my_callback;

	// Objects
	JN_Plunger* plunger;

	void CreateFrame();
	void CreatePlane();
	void CreateBall();

	void AddObjects();

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

