#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Config.h"

class World {
public:
	void start();
	static World* getInstance();
	sf::RenderWindow* getWindow();
	void insertGameObject(GameObject*);
	void removeGameObject(GameObject*);
	void sendMessage(InputHandler::Message);
	void update();
	void render();
	enum Object { PLAYER, ENEMY, BALL };
	GameObject* getObj(Object);
	b2World* getCollWorld();
	void setPlayer(GameObject*);
	void setObj(GameObject*, Object);
private:
	World();
	static World* instance;
	static bool worldExists;
	std::list<GameObject*> objects;
	sf::RenderWindow* myWindow;
	sf::RectangleShape* bg;
	GameObject* player;
	GameObject* ball;
	GameObject* enemy;
	b2World* myWorld;
};