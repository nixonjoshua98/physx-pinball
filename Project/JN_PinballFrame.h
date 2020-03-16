#pragma once

#include "JN_Model.h"

#include <string>

class JN_PinballFrame
{
public:
	JN_PinballFrame();

	void AddToScene(JN_Scene* scene);

private:
	JN_Model* model;

	void Create();
};

