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

sf::RectangleShape * GameObject::getModel() { return model; }

sf::Vector2f GameObject::getPosition() { return model == NULL ? sf::Vector2f(0, 0) : model->getPosition(); }

sf::Vector2f GameObject::getVelocity() { return sf::Vector2f(0, 0); }
