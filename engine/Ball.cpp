#include "stdafx.h"
#include "Ball.h"


Ball::Ball() {
	World::getInstance()->insertGameObject(this);
}


Ball::~Ball() {
	World::getInstance()->removeGameObject(this);
}


void Ball::Start(sf::Vector2f vec) {
	model = new sf::RectangleShape();
	model->setSize(sf::Vector2f(8, 8));
	model->setPosition(vec);
	model->setFillColor(sf::Color::White);
}

void Ball::update() {

}

sf::RectangleShape * Ball::getModel() {
	return model;
}

void Ball::receiveMessage(InputHandler::Message) {

}
