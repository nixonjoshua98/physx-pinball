#pragma once

#include "JN_Scene.h"

#include "MyPhysicsEngine.h"

#include "JN_Paddle.h"
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
	JN_Paddle* paddle;


	MySimulationEventCallback* my_callback;

	void CreateFrame();
	void CreatePaddles();

	void CustomInit() override;
	void CustomUpdate(PxReal delta) override;
};

