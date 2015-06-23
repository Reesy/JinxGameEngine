//
//  GameEngine.h
//  VRBreakout
//
//  Created by James Rees on 08/05/2015.
//  Copyright (c) 2015 James Rees. All rights reserved.
//

#ifndef __VRBreakout__GameEngine__
#define __VRBreakout__GameEngine__
#pragma unmanaged

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL\SOIL.h>
#include "Shader.h"
#include "GameObject.h"
#include "SquareObject.h"
#include "CircleObject.h"
#include "CubeObject.h"
#include "TextRender.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
struct State{
	bool paused;
	bool menu;
	bool debugMode;


};

class GameEngine{
    GLFWwindow* window;
    int WIDTH = 1600;
    int HEIGHT = 900;
 
    glm::mat4 model;
    glm::mat4 view;
	glm::mat4 orthView;
    glm::mat4 projection;
	glm::mat4 orthProjection;

    double xpos, ypos;
	
	
public:
	bool paused;

    GameEngine(GLFWwindow * window);
    ~GameEngine();
    
	void GameMain();
    void input();
  //  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	//static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    void render();
    void update();
    void debugMode();
	void menuMode();
	void handleMouseEvent(int, int);
	void handleKeyEvent(int, int);
	bool checkCollision(GameObject, GameObject); //Checks if Object A is within the bounds of Object B
	
};


#endif /* defined(__VRBreakout__GameEngine__) */
