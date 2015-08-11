#include "GameObjects.h"


class GraphicsComponent{

public:


	//pass gameobject to use vector3f
	virtual	void update(GameObjects& gameObject);
	virtual void draw(MVPState currentState);

};