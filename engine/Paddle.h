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
	void start(int, int, sf::Vector2f);
	void update();
	void receiveMessage(InputHandler::Message);
	void setPlayer();
	void move(InputHandler::Message);
	sf::Vector2f getVelocity();
private:
	bool isPlayer = false;
	sf::Vector2f velocity = sf::Vector2f(0,0);
	int acceleration = 200; // acceleration is pixels per 16 ms
	int speed = SCREEN_Y; // speed is pixels per second
};

