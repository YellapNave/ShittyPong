#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject()
{
	delete this;
}

void GameObject::update() {}

void GameObject::start() {}

void GameObject::receiveMessage(InputHandler::Message) {};

sf::RectangleShape * GameObject::getModel() { return NULL; }

