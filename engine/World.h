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
	enum Object { PLAYER, ENEMY, BALL};
	GameObject* getObject(Object);
	void setObject(Object, GameObject*);
private:
	World();
	void score(Object);
	static World* instance;
	static bool worldExists;
	std::list<GameObject*> objects;
	sf::RenderWindow* myWindow;
	sf::RectangleShape* bg;
	GameObject* player;
	GameObject* enemy;
	GameObject* ball;
};