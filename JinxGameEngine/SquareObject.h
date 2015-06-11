#pragma once
#include "GameObject.h"

struct size{
	float x, y, z;
};
class SquareObject : public GameObject
{

public:
	size SquareSize;
	SquareObject();
	~SquareObject();

	void draw(glm::mat4 &view, glm::mat4 &projection);
	void drawBounds();
	void init(Shader);
};

