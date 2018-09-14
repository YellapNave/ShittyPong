#pragma once
#include "stdafx.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
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
protected:
	sf::RectangleShape * model;
};

