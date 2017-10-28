//
//  GameEngine.cpp
//  VRBreakout
//
//  Created by James Rees on 08/05/2015.
//  Copyright (c) 2015 James Rees. All rights reserved.
// 1 unit is 1meter
#include "GameEngine.h"
float ballvelocity;
float velocity = 0.0f;

bool movingLeft;
bool movingRight;
int LeftButton;
bool beingClicked;

CubeObject cube;
GameState mainState;
SquareObject cursor;
SquareObject testBox;
SquareObject resumeBox;
SquareObject settingsBox;
SquareObject exitBox;
TextRender textRender;

GameEngine::GameEngine(GLFWwindow * currentWindow){
	window = currentWindow;
};

GameEngine::~GameEngine(){
}
void GameEngine::GameLoop(){
		//Initialising code
		Shader mainShader("../resources/VertexShader.vert", "../resources/FragmentShader.frag");
		Shader menuShader("../resources/VertexShader2D.vert", "../resources/FragmentShader2D.frag");

		cube.init(mainShader);
		cube.setColor(1.0f, 0.0f, 1.0f);
		cube.setSize(1, 1, 1);
		cube.translateX(4);
		
		testBox.init(mainShader);
		testBox.setColor(0.0f, 1.0f, 1.0f);
		testBox.setSize(1.0f, 1.0f, 1.0f);
		testBox.setTexture("../resources/awesomeface.png");

		resumeBox.init(menuShader);
		resumeBox.setColor(0.0f, 1.0f, 1.0f);
		resumeBox.setSize(190.0f, 45.0f, 1.0f);
		resumeBox.translate(790, 520, 0);

		settingsBox.init(menuShader);
		settingsBox.setColor(1.0f, 0.0f, 1.0f);
		settingsBox.setSize(190.0f, 45.0f, 1.0f);
		settingsBox.translate(790, 467, 0);

		exitBox.init(menuShader);
		exitBox.setColor(1.0f, 1.0f, 0.0f);
		exitBox.setSize(190.0f, 45.0f, 1.0f);
		exitBox.translate(790, 415, 0);

		textRender.init(1600, 900);

		cursor.init(menuShader);
		cursor.setSize(5.0f, 5.0f, 5.0f);

        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0, 0, -10));
		
		orthProjection = glm::ortho(0.0f, static_cast<GLfloat>(1600), 0.0f, static_cast<GLfloat>(900));

		orthView = glm::translate(orthView, glm::vec3(0, 0, -1)); //this is blank to reuse same mainShader 
		
		


		// main loop
        while (!glfwWindowShouldClose(window)){
            glfwPollEvents();
			update();
			//glfwGetCursorPos(window, &xpos, &ypos); 
            render();
        }
       glfwTerminate();
}

void GameEngine::handleMouseEvent(int button, int action){

	if (mainState.menu){
		if (checkCollision(cursor, resumeBox) && LeftButton == GLFW_PRESS){
			mainState.menu = false;
		}
		else if (checkCollision(cursor, settingsBox) && LeftButton == GLFW_PRESS){
			mainState.debugMode = !mainState.debugMode;
		}
		else if (checkCollision(cursor, exitBox) && LeftButton == GLFW_PRESS){
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void GameEngine::handleKeyEvent(int key, int action){


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		mainState.menu = !mainState.menu;

	if (mainState.menu){
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){

		std::cout << "***************************************************************************************" << std::endl;
		std::cout << "cursor position  : " << cursor.getPosition().x << " " << cursor.getPosition().y << " " << cursor.getPosition().z << std::endl;
		std::cout << "cursor  box size :" << cursor.getSize().x << " " << cursor.getSize().y << " " << cursor.getSize().z << std::endl;
		std::cout << "cursor  Box Left :" << cursor.getBounds().left << "   " << "Exit Box Left:" << exitBox.getBounds().left << std::endl;
		std::cout << "cursor  Box RIGHT:" << cursor.getBounds().right << "   " << "Exit Box Right:" << exitBox.getBounds().right << std::endl;
		std::cout << "cursor  Box UP   :" << cursor.getBounds().up << "   " << "   Exit Box up:" << exitBox.getBounds().up << std::endl;
		std::cout << "cursor  Box DOWN :" << cursor.getBounds().down << "   " << "Exit Box down:" << exitBox.getBounds().down << std::endl;
		std::cout << "cursor  Box FRONT:" << cursor.getBounds().front << "   " << "Exit Box front:" << exitBox.getBounds().front << std::endl;
		std::cout << "cursor  Box BACK :" << cursor.getBounds().back << "   " << "Exit Box back:" << exitBox.getBounds().back << std::endl;
	}
	if (key == GLFW_KEY_UP    && action == GLFW_PRESS){
		resumeBox.translateY(10);
	}
	if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS){
		resumeBox.translateY(-10);
	}
	if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS){
		resumeBox.translateX(-10);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		resumeBox.translateX(10);
	}
	if (key == GLFW_KEY_P     && action == GLFW_PRESS){
		mainState.paused = !mainState.paused;
	}
	if (key == GLFW_KEY_TAB   && action == GLFW_PRESS){
		mainState.debugMode = !mainState.debugMode;
	}

}

void GameEngine::render(){
	//clears screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//render code:
	
	testBox.draw(this->view, this->projection);
	cube.draw(this->view, this->projection);
	
    if (mainState.menu == true){ menuMode(); }
	if (mainState.paused == true){
		textRender.RenderText("Paused", 700.0f, 450.0f, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
	}
	if (mainState.debugMode == true){ debugMode(); }
	glfwSwapBuffers(window);
}
void GameEngine::menuMode(){
	textRender.RenderText("Resume  ", 700.0f, 500.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
	textRender.RenderText("Settings", 700.0f, 450.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
	textRender.RenderText("Exit    ", 700.0f, 400.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
}
void GameEngine::update(){
	glfwGetCursorPos(window, &xpos, &ypos);
	LeftButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	cursor.setPosition(xpos, (-ypos + 900), 1.0f);
	
}
void GameEngine::debugMode(){
	
	textRender.RenderText("Debug Information  ", 25.0f, 850.0f, 0.6f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText("Mouse x Position:  ", 25.0f, 830.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText("Mouse y Position:  ", 25.0f, 810.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	std::ostringstream xstring, ystring;
	xstring << xpos; ystring << -ypos + 900;

	textRender.RenderText(xstring.str(), 150.0f, 830.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText(ystring.str(), 150.0f, 810.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));

	settingsBox.draw(this->view, this->orthProjection);
	resumeBox.draw(this->view, this->orthProjection);
	exitBox.draw(this->view, this->orthProjection);
    
}

//Checks if part of A is inside the bounds of B
bool GameEngine::checkCollision(GameObject A, GameObject B){
	if (A.getBounds().right > B.getBounds().left && A.getBounds().left < B.getBounds().right && 
		A.getBounds().up > B.getBounds().down && A.getBounds().down < B.getBounds().up &&
		A.getBounds().front > B.getBounds().back && A.getBounds().back < B.getBounds().front){
		return true;
	}
	return false;
}


