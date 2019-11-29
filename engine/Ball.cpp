#include "stdafx.h"
#include "Ball.h"


Ball::Ball() {
	World::getInstance()->insertGameObject(this);
	World::getInstance()->setObject(World::Object::BALL, this);
}


Ball::~Ball() {
	World::getInstance()->removeGameObject(this);
}


void Ball::start() {
	model = new sf::RectangleShape();
	model->setSize(sf::Vector2f(BALL_SIZE, BALL_SIZE));
	model->setFillColor(sf::Color::Cyan);
}

void Ball::update() {
	if (!launched)
		model->setPosition(World::getInstance()->getObject(World::Object::PLAYER)->getPosition() + sf::Vector2f(-BALL_SIZE - 12, PHEIGHT / 2 - BALL_SIZE / 2));

	sf::Vector2f position = model->getPosition();
	sf::Vector2f playerPosition = World::getInstance()->getObject(World::Object::PLAYER)->getPosition();
	sf::Vector2f enemyPosition = World::getInstance()->getObject(World::Object::ENEMY)->getPosition();

	// bounce vertically
	if (position.y <= BG_OUTLINE_THICKNESS && velocity.y < 0)
		reverseVelocity(GameObject::Axis::Y);
	else if (position.y >= (SCREEN_Y - BG_OUTLINE_THICKNESS - BALL_SIZE) && velocity.y > 0)
		reverseVelocity(GameObject::Axis::Y);
	
	// enemy hits the ball
	if (position.x <= enemyPosition.x + BALL_SIZE && position.x >= enemyPosition.x && !playerTurn) {
		if (position.y > (enemyPosition.y - BALL_SIZE) && position.y < (enemyPosition.y + PHEIGHT)) {
			reverseVelocity(GameObject::Axis::X);
			velocity += World::getInstance()->getObject(World::Object::ENEMY)->getVelocity();
			playerTurn = !playerTurn;
		}
	}

	// player hits the ball
	else if (position.x >= (playerPosition.x - BALL_SIZE) && position.x <= (playerPosition.x + BALL_SIZE) && playerTurn) {
		if (position.y >(playerPosition.y - BALL_SIZE) && position.y < (playerPosition.y + PHEIGHT)) {
			reverseVelocity(GameObject::Axis::X);
			velocity += World::getInstance()->getObject(World::Object::PLAYER)->getVelocity();
			playerTurn = !playerTurn;
		}
	}

	if (position.x <= BG_OUTLINE_THICKNESS) {
		World::getInstance()->sendMessage(InputHandler::Message::SCORE_PLAYER);
		launched = false;
		velocity = sf::Vector2f(0,0);
	}
	else if (position.x >= (SCREEN_X - BG_OUTLINE_THICKNESS - BALL_SIZE)) {
		World::getInstance()->sendMessage(InputHandler::Message::SCORE_ENEMY);
		launched = false;
		velocity = sf::Vector2f(0, 0);
	}

	if (abs(velocity.y) > speed) {
		velocity.y = velocity.y < 0 ? -speed : speed;
	}
	if (abs(velocity.x) > speed) {
		velocity.x = velocity.x < 0 ? -speed : speed;
	}
		
	model->setPosition(model->getPosition() + (SCALE * velocity));
}

void Ball::receiveMessage(InputHandler::Message msg) {
	switch (msg) {
	case InputHandler::Message::LAUNCH:
		if (!launched) {
			launched = true;
			playerTurn = false;
			velocity = sf::Vector2f(-speed, World::getInstance()->getObject(World::Object::PLAYER)->getVelocity().y);
		}
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
	};
}