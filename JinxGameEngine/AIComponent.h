#pragma once
#include "GameObjects.h"

class AIComponent
{
public:
	AIComponent();
	virtual void update(GameObjects &gameObject);
};

