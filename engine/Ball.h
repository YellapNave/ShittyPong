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
	void start();
	void update();
	void receiveMessage(InputHandler::Message);
	void reverseVelocity(Axis);
private:
	bool launched = false;
	bool playerTurn = false;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	int speed = SCREEN_Y * 0.75;
};

