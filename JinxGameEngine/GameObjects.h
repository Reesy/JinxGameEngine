
#ifndef __GameObjects__
#define __GameObjects__
#pragma unmanaged

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "PhysicsComponent.h"
#include "AIComponent.h"
#include "GraphicsComponent.h"


class GameObjects{
	AIComponent* AI;
	GraphicsComponent* Graphics;
	PhysicsComponent* Physics;

	glm::vec3 rotation; //possibly change to quaternion?
	glm::vec3 position; //x, y, z world co-ords
	MVPState currentState;

	
	GameObjects(AIComponent* AI, GraphicsComponent* Graphics, PhysicsComponent* Physics)
		:AI(AI),
		Graphics(Graphics),
		Physics(Physics)
	{
		this->setPosition(glm::vec3(0, 0, 0));
		this->setRotation(glm::vec3(0, 0, 0));
	}
	

public:
	//GameObjects();

	~GameObjects();
	void update(){
		AI->update(*this);
		Graphics->update(*this);
		Physics->update(*this);
	}

	//Accessors and mutators
	glm::vec3 getRotation();
	void setRotation(glm::vec3 inputRotation);
	
	glm::vec3 getPosition();
	void setPosition(glm::vec3 inputPosition);
};
#endif // !__GameObjects__