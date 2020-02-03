#pragma once

#include "JN_Scene.h"

#include "MyPhysicsEngine.h"

using namespace PhysicsEngine;

#include "JN_BasicActors.h"


class JN_PinballScene : public JN_Scene
{
public:
	JN_PinballScene();

	void SetVisualisation();

	// Events
	void OnKeyPressed(char key);
	void OnKeyReleased(char key);

private:
	Actors::Plane* plane;
	Actors::Sphere* ball;

	MySimulationEventCallback* my_callback;

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

