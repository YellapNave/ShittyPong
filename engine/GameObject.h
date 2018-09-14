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
	virtual sf::RectangleShape * getModel();
};

