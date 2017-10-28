#pragma once
#include "GameObject.h"

class CircleObject :
	public GameObject
{
public:
	CircleObject();
	~CircleObject();

	void draw(glm::mat4 &view, glm::mat4 &projection);
	void drawBounds();
	void init(Shader);
};

