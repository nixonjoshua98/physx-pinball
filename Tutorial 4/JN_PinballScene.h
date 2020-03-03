#pragma once

#include "MyPhysicsEngine.h"

#include "JN_Scene.h"

#include "JN_BasicActors.h"
#include "JN_Plunger.h"
#include "JN_Model.h"


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

	// Materials
	PxMaterial* ballMaterial;

	// Objects
	JN_Plunger* plunger;
	JN_Model* frame;

	void CreatePlane();
	void CreateBall();
	void CreateFrame();
	void CreateHexagons();
	void CreatePlunger();
	void CreateSpinner();

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

