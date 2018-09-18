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
		velocity = World::getInstance()->getObj(World::Object::PLAYER)->getVelocity();

	if (model->getPosition().x > 500 && model->getPosition().y < 750 && bounced) {
		bounced = false;
	}

	if (model->getPosition().y <= BG_OUTLINE_THICKNESS && velocity.y < 0)
		velocity = reverseVelocity(GameObject::Axis::Y);
	else if (model->getPosition().y >= (SCREEN_Y - BG_OUTLINE_THICKNESS - BALL_SIZE) && velocity.y > 0)
		velocity = reverseVelocity(GameObject::Axis::Y);
	
	if (World::getInstance()->getCollWorld()->GetContactList()) {
		if (!bounced) {
			sf::Vector2f tempVel = reverseVelocity(GameObject::Axis::X);
			velocity = tempVel;
			bounced = true;
		}
	}

	// add scoring here
	if (model->getPosition().x <= BG_OUTLINE_THICKNESS) {
		launched = false;
	}
	else if (model->getPosition().x >= SCREEN_X - BG_OUTLINE_THICKNESS - BALL_SIZE) {
		launched = false; 
	}
	

	model->setPosition(model->getPosition() + (SCALE * velocity));
	myBody->SetLinearVelocity(b2Vec2(velocity.x / PIXELS_TO_METERS, velocity.y / PIXELS_TO_METERS));
}

void Ball::receiveMessage(InputHandler::Message msg) {
	switch (msg) {
	case InputHandler::Message::LAUNCH:
		launched = true;
		velocity = sf::Vector2f(-speed, World::getInstance()->getObj(World::Object::PLAYER)->getVelocity().y);
		break;
	}
}

sf::Vector2f Ball::reverseVelocity(Axis axis) {
	sf::Vector2f tempVel = velocity;
	switch (axis) {
	case GameObject::Axis::X: 
		tempVel.x = -velocity.x;
		break;
	case GameObject::Axis::Y:
		tempVel.y = -velocity.y;
		break;
	}

	return tempVel;
}