#ifndef __GRAPHICSCOMPONENT__
#define __GRAPHICSCOMPONENT__


class GameObjects;

class GraphicsComponent{

public:
	virtual void update(GameObjects& gameObjects);
};

#endif