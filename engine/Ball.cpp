#include "stdafx.h"
#include "Ball.h"


Ball::Ball() {
	World::getInstance()->insertGameObject(this);
}


Ball::~Ball() {
	World::getInstance()->removeGameObject(this);
}


void Ball::start() {
	model = new sf::RectangleShape();
	model->setSize(sf::Vector2f(BALL_SIZE, BALL_SIZE));
	model->setFillColor(sf::Color::White);
}

void Ball::update() {
	if (!launched)
		model->setPosition(World::getInstance()->getPlayer()->getPosition() + sf::Vector2f(-BALL_SIZE - 12, PHEIGHT / 2 - BALL_SIZE / 2));

	if (model->getPosition().y <= BG_OUTLINE_THICKNESS && velocity.y < 0)
		reverseVelocity(GameObject::Axis::Y);
	else if (model->getPosition().y >= (SCREEN_Y - BG_OUTLINE_THICKNESS - BALL_SIZE) && velocity.y > 0)
		reverseVelocity(GameObject::Axis::Y);
	
	if (model->getPosition().x <= BG_OUTLINE_THICKNESS) {
		reverseVelocity(GameObject::Axis::X);
	}
	else if (model->getPosition().x >= SCREEN_X - BG_OUTLINE_THICKNESS - BALL_SIZE) {
		reverseVelocity(GameObject::Axis::X);
	}
		
	model->setPosition(model->getPosition() + (SCALE * velocity));
}

void Ball::receiveMessage(InputHandler::Message msg) {
	switch (msg) {
	case InputHandler::Message::LAUNCH:
		launched = true;
		velocity = sf::Vector2f(-speed, World::getInstance()->getPlayer()->getVelocity().y);
		break;
	}
}

void Ball::reverseVelocity(Axis axis) {
	sf::Vector2f tempVel = velocity;
	switch (axis) {
	case GameObject::Axis::X: 
		tempVel.x = -velocity.x;
		velocity = tempVel;
		break;
	case GameObject::Axis::Y:
		tempVel.y = -velocity.y;
		velocity = tempVel;
		break;
	}
}