#include "GameObjects.h"

//Accessors 


glm::vec3 GameObjects::getRotation(){
	return this->rotation;
}

glm::vec3 GameObjects::getPosition(){
	return this->position;
}

//Mutators
void GameObjects::setRotation(glm::vec3 inputRotation){
	this->rotation = inputRotation;
}

void GameObjects::setPosition(glm::vec3 inputPosition){
	this->position = inputPosition;
}

