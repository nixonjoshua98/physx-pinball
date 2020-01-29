#pragma once


#include "JN_Scene.h"

// This has Cloth, Plane etc.
#include "MyPhysicsEngine.h"

using namespace PhysicsEngine;


class JN_PinballScene : public JN_Scene
{
public:
	JN_PinballScene();

	void SetVisualisation();

	// Events
	void OnKeyPressed(char key);
	void OnKeyReleased(char key);

private:
	Plane* plane;
	Cloth* cloth;
	Box* box;
	MySimulationEventCallback* my_callback;

	void CustomInit() override;
	void CustomUpdate() override;
};

