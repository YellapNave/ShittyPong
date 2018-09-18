#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle()
{
	World::getInstance()->insertGameObject(this);
}

void Paddle::start(int x, int y, sf::Vector2f vec) {
	model = new sf::RectangleShape();
	model->setSize(sf::Vector2f(x, y));
	model->setPosition(vec);
	model->setFillColor(sf::Color::White);
}

Paddle::~Paddle()
{
	World::getInstance()->removeGameObject(this);
}

void Paddle::update() {
	if (model->getPosition().y <= BG_OUTLINE_THICKNESS && velocity.y < 0)
		velocity = sf::Vector2f(0, 0);
	else if (model->getPosition().y >= (SCREEN_Y - BG_OUTLINE_THICKNESS - PHEIGHT) && velocity.y > 0)
		velocity = sf::Vector2f(0, 0);

	model->setPosition(model->getPosition() + (SCALE * velocity));
	myBody->SetLinearVelocity(b2Vec2(0, velocity.y / PIXELS_TO_METERS));
}

void Paddle::receiveMessage(InputHandler::Message msg) {
	if (isPlayer) { // if the player gives input and the current object is the player, move it
		switch (msg) {
		case InputHandler::Message::PLAYER_MOVE_UP:
			move(msg);
			break;
		case InputHandler::Message::PLAYER_MOVE_DOWN:
			move(msg);
			break;
		case InputHandler::Message::PLAYER_SLOW:
			move(msg);
			break;
		}
	}
	else { // if the current object is not the player and the enemy gives input, move it
		switch (msg) {
		case InputHandler::Message::ENEMY_MOVE_UP:
			move(InputHandler::Message::PLAYER_MOVE_UP);
			break;
		case InputHandler::Message::ENEMY_MOVE_DOWN:
			move(InputHandler::Message::PLAYER_MOVE_DOWN);
			break;
		case InputHandler::Message::ENEMY_SLOW:
			move(InputHandler::Message::PLAYER_SLOW);
			break;
		}
	}
}

void Paddle::move(InputHandler::Message msg) {
	switch (msg) {
	case InputHandler::Message::PLAYER_SLOW:
		if (velocity.y < 0)
			velocity += sf::Vector2f(0, acceleration);
		else if (velocity.y > 0)
			velocity += sf::Vector2f(0, -acceleration);
		break;
	case InputHandler::Message::PLAYER_MOVE_UP:
		if (velocity.y > -speed)
			velocity += sf::Vector2f(0, -acceleration);
		break;
	case InputHandler::Message::PLAYER_MOVE_DOWN:
		if (velocity.y < speed)
			velocity += sf::Vector2f(0, acceleration);
		break;
	}
}

sf::Vector2f Paddle::getVelocity() {
	return velocity;
}

void Paddle::setPlayer() {
	isPlayer = true;
}