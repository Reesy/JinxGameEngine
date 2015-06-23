//
//  GameObject.cpp
//  VRBreakout
//
//  Created by James Rees on 08/05/2015.
//  Copyright (c) 2015 James Rees. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(){
    
};

GameObject::~GameObject(){

};

void GameObject::setPosition(float x, float y, float z){
    this->Position.x = x;
    this->Position.y = y;
    this->Position.z = z;

	updateBounds(); 
}

void GameObject::setPosition(glm::vec3 position){
    this->Position = position;

	updateBounds();
}


glm::vec3 GameObject::getSize(){

	return this->Scale;

}

void GameObject::setSize(float x, float y, float z){
    this->Scale.x = x;
    this->Scale.y = y;
    this->Scale.z = z;
	

	updateBounds();
	

}
//this overload is to manually set the size of the bounds.
void GameObject::setBounds(float x, float y, float z){
	


}

void GameObject::updateBounds(){
	this->thisBounds.up = this->Position.y + (this->Scale.y / 2) ;
	this->thisBounds.down = this->Position.y - (this->Scale.y / 2);
	this->thisBounds.front = this->Position.z + (this->Scale.z / 2);
	this->thisBounds.back = this->Position.z - (this->Scale.z / 2);
	this->thisBounds.left = this->Position.x - (this->Scale.x / 2);
	this->thisBounds.right = this->Position.x + (this->Scale.x / 2);


}
bounds GameObject::getBounds(){

	return this->thisBounds;

}
void GameObject::setX(float x){
    this->Position.x = x;

	updateBounds();
}

void GameObject::setY(float y){
    this->Position.y = y;


	updateBounds();

}
void GameObject::setZ(float z){
    this->Position.z = z;
	
	updateBounds();
}

void GameObject::translateX(float x){
	this->Position.x += x;

	updateBounds();

}
void GameObject::translateY(float y){
	this->Position.y += y;

	updateBounds();

}
void GameObject::translateZ(float z){
	this->Position.z += z;

	updateBounds();

}
void GameObject::translate(float x, float y, float z){
	this->Position.x += x;
	this->Position.y += y;
	this->Position.z += z;

	updateBounds();

}

glm::vec3 GameObject::getPosition(){
    return this->Position;



}

void GameObject::setVelocity(float vel){
	this->velocity = vel;
}

void GameObject::setTexture(const char* filepath){

	this->hasTexture = true;
	int width, height;
	unsigned char* image;

	//Textues are loaded here.

	image = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGB);
	SOIL_free_image_data(image);
	this->texture.Generate(width, height, image);



}
void GameObject::setColor(float r, float g, float b){

	this->color.x = r;
	this->color.y = g;
	this->color.z = b;

}
