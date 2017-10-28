#ifndef __GRAPHICSCOMPONENT__
#define __GRAPHICSCOMPONENT__



class GameObjects;
//This struct will hold view and projection state of the scene, Model will be defined by the Component
//may need to be pushed up to main
struct MVPState {

	glm::mat4 View;
	glm::mat4 Projection;


};
class GraphicsComponent{
	GLint modelLocation; //Unform for model
	GLint viewLocation; //uniform for view
	GLint projectionLocation; //uniform for projection
	Shader myShader;
public:
	GraphicsComponent(Shader& inputShader);
	virtual void update(GameObjects& gameObjects);
	virtual void draw(MVPState& currentState);
};

#endif