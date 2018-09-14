#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "World.h"

class Ball : 
	public GameObject
{
public:
	Ball();
	~Ball();
	void Start(sf::Vector2f);
	void update();
	sf::RectangleShape * getModel();
	void receiveMessage(InputHandler::Message);
private:
	sf::RectangleShape * model;
	int speed = 1;
};

