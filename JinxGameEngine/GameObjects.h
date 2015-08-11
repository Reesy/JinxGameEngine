
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include <SOIL/SOIL.h>


//This struct will hold view and projection state of the scene, Model will be defined by the Component
struct MVPState{

	glm::mat4 View;
	glm::mat4 Projection;


};

class GameObjects{
	glm::vec3 rotation; //possibly change to quaternion?
	glm::vec3 translation; //x, y, z world co-ords

public:
	GameObjects(Shader &myShader);
	~GameObjects();
	void update();


};