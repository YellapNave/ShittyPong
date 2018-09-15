#pragma once
#include "stdafx.h"
#include "InputHandler.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void update();
	virtual void start();
	virtual void receiveMessage(InputHandler::Message);
	sf::RectangleShape * getModel();
	sf::Vector2f getPosition();
	virtual sf::Vector2f getVelocity();
	enum Axis { X, Y };
	void setBody(b2Body*);
	b2Body* getBody();
protected:
	sf::RectangleShape * model;
	b2Body* myBody;
};

