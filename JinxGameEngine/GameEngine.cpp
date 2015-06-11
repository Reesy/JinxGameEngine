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

CubeObject cube;
State mainState;
SquareObject testBox;
SquareObject resumeBox;
SquareObject settingsBox;
SquareObject exitBox;
TextRender textRender;

GameEngine::GameEngine(){
    GameMain(); 
};

GameEngine::~GameEngine(){
}
void GameEngine::GameMain(){
 
        glfwInit();
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
        window = glfwCreateWindow(WIDTH, HEIGHT, "VR Breakout!", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetKeyCallback(window, this->key_callback);
   
        glewExperimental = GL_TRUE;
        glewInit();
        glEnable(GL_DEPTH_TEST);
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT); // Mac specific, used for fixing NDC
    
        glViewport(0, 0, WIDTH, HEIGHT);
		
		Shader mainShader("resources/VertexShader.vert", "resources/FragmentShader.frag");
		Shader menuShader("resources/VertexShader2D.vert", "resources/FragmentShader2D.frag");
		cube.init(mainShader);
		cube.setColor(1.0f, 0.0f, 1.0f);
		cube.setSize(1, 1, 1);
		cube.translateX(4);
	
		testBox.init(mainShader);
		testBox.setColor(0.0f, 1.0f, 1.0f);
		testBox.setSize(1.0f, 1.0f, 1.0f);

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

        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0, 0, -10));
		
		orthProjection = glm::ortho(0.0f, static_cast<GLfloat>(1600), 0.0f, static_cast<GLfloat>(900));

		orthView = glm::translate(orthView, glm::vec3(0, 0, -1)); //this is blank to reuse same mainShader 
		// main loop
        while (!glfwWindowShouldClose(window)){
            glfwPollEvents();
			update();
			glfwGetCursorPos(window, &xpos, &ypos); 
           // render();
        }
        glfwTerminate();
}
void GameEngine::input(){
	
}
void GameEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		mainState.menu = !mainState.menu;
	if (mainState.menu){
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		std::cout << "***************************************************************************************" << std::endl;
		std::cout << "Resume box position: " << resumeBox.getPosition().x << " " << resumeBox.getPosition().y << " " << resumeBox.getPosition().z << std::endl;
		std::cout << "Resume Box Left:"  << resumeBox.getBounds().left <<  "   " << "Exit Box Left:" << exitBox.getBounds().left  << std::endl;
		std::cout << "Resume Box RIGHT:" << resumeBox.getBounds().right << "   " << "Exit Box Right:" << exitBox.getBounds().right << std::endl;
		std::cout << "Resume Box UP   :" << resumeBox.getBounds().up << "   " << "   Exit Box up:" << exitBox.getBounds().up << std::endl;
		std::cout << "Resume Box DOWN :" << resumeBox.getBounds().down << "   " <<  "Exit Box down:" << exitBox.getBounds().down << std::endl;
		std::cout << "Resume Box FRONT:" << resumeBox.getBounds().front << "   " << "Exit Box front:" << exitBox.getBounds().front << std::endl;
		std::cout << "Resume Box BACK :" << resumeBox.getBounds().back << "   " <<  "Exit Box back:" << exitBox.getBounds().back << std::endl;
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
	//testBox.setTexture("resources/awesomeface.png");
	cube.draw(this->view, this->projection);
	


	//resumeBox.draw(this->view, this->projection);
	if (mainState.debugMode == true){ debugMode();}
    if (mainState.menu == true){ menuMode(); }
	if (mainState.paused == true){
		textRender.RenderText("Paused", 700.0f, 450.0f, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
	}
	settingsBox.draw(this->view, this->orthProjection);
	resumeBox.draw(this->view, this->orthProjection);
	exitBox.draw(this->view, this->orthProjection);
	glfwSwapBuffers(window);
}
void GameEngine::menuMode(){
	textRender.RenderText("Resume  ", 700.0f, 500.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
	textRender.RenderText("Settings", 700.0f, 450.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
	textRender.RenderText("Exit    ", 700.0f, 400.0f, 1.0f, glm::vec3(0.0, 0.0f, 1.0f));
}
void GameEngine::update(){

	checkCollision(resumeBox, exitBox);
	
}
void GameEngine::debugMode(){
	
	textRender.RenderText("Debug Information  ", 25.0f, 850.0f, 0.6f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText("Mouse x Position:  ", 25.0f, 830.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText("Mouse y Position:  ", 25.0f, 810.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	std::ostringstream xstring, ystring;
	xstring << xpos; ystring << -ypos + 900;

	textRender.RenderText(xstring.str(), 150.0f, 830.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
	textRender.RenderText(ystring.str(), 150.0f, 810.0f, 0.3f, glm::vec3(0.1, 0.8f, 0.2f));
    
}

//Checks if part of A is inside the bounds of B
bool GameEngine::checkCollision(GameObject A, GameObject B){
	if (A.getBounds().right > B.getBounds().left && A.getBounds().left < B.getBounds().right && 
		 A.getBounds().down < B.getBounds().up && A.getBounds().up > B.getBounds().down ){
		std::cout << "ding";
	}
	return true;
}