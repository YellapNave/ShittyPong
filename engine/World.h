#pragma once
#include "stdafx.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include "GameObject.h"
#include "InputHandler.h"
#include "Config.h"

class World {
public:
	void Start();
	static World* getInstance();
	sf::RenderWindow* getWindow();
	void insertGameObject(GameObject*);
	void removeGameObject(GameObject*);
	void sendMessage(InputHandler::Message);
	void update();
	void render();
private:
	World();
	static World* instance;
	static bool worldExists;
	std::list<GameObject*> objects;
	sf::RenderWindow* myWindow;
	sf::RectangleShape* bg;
};