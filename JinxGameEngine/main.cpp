//
//  main.cpp
//  VRBreakout
//
//  Created by James Rees on 08/05/2015.
//  Copyright (c) 2015 James Rees. All rights reserved.
//
#include "GameEngine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL\SOIL.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main(int argc, const char * argv[]) {
	GLFWwindow* window;
	int WIDTH = 1600;
	int HEIGHT = 900;
	
	
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Jinx Engine", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, true);
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glfwGetFramebufferSize(window, &WIDTH, &HEIGHT); // Mac specific, used for fixing NDC
	glViewport(0, 0, WIDTH, HEIGHT);

    GameEngine mainEngine(window);

	glfwSetWindowUserPointer(window, &mainEngine);

	mainEngine.GameLoop();
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	GameEngine * game = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));
	game->handleKeyEvent(key, action);
}


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	GameEngine * game = reinterpret_cast<GameEngine *>(glfwGetWindowUserPointer(window));
	game->handleMouseEvent(button, action);
}

