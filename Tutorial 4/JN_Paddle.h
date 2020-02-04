#pragma once

#include "JN_BasicActors.h"

class JN_Paddle
{
public:
	JN_Paddle();
	~JN_Paddle();

	Actors::Actor* GetActor();

	void Activate();

private:
	Actors::Box* actor;
};

