#include "JN_Paddle.h"



JN_Paddle::JN_Paddle()
{
	actor = new Actors::Box({ -4.0f, 0.5f, 13.0f }, { 2.0f, 0.5f, 0.5f });

	actor->SetKinematic(true);
}


JN_Paddle::~JN_Paddle()
{

}

Actors::Actor* JN_Paddle::GetActor()
{
	return actor;
}

void JN_Paddle::Activate()
{

}
