#pragma once
#include "GameObject.h"
class CubeObject :
	public GameObject
{
public:
	CubeObject();
	~CubeObject();

	void draw(glm::mat4 &view, glm::mat4 &projection);
	void drawBounds();
	void init(Shader);
};

