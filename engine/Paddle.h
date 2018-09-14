#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "World.h"

class Paddle :
	public GameObject
{
public:
	Paddle();
	~Paddle();
	void Start(int, int, sf::Vector2f);
	void update();
	sf::RectangleShape * getModel();
	void receiveMessage(InputHandler::Message);
	void setPlayer();
	void move(InputHandler::Message);
private:
	sf::RectangleShape * model;
	bool isPlayer = false;
	sf::Vector2f velocity = sf::Vector2f(0,0);
	int speed = 1; // speed is pixels per second
};

