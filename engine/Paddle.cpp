#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle()
{
	World::getInstance()->insertGameObject(this);
}

void Paddle::Start(int x, int y, sf::Vector2f vec) {
	model = new sf::RectangleShape();
	model->setSize(sf::Vector2f(x, y));
	model->setPosition(vec);
	model->setFillColor(sf::Color::White);
}

Paddle::~Paddle()
{
	World::getInstance()->removeGameObject(this);
}

void Paddle::update() {}

sf::RectangleShape * Paddle::getModel() {
	return model;
}

void Paddle::receiveMessage(InputHandler::Message msg) {
	if (!isPlayer)
		return;
	switch (msg) {
	case InputHandler::Message::PLAYER_MOVE_UP:
		move(msg);
		break;
	case InputHandler::Message::PLAYER_MOVE_DOWN:
		move(msg);
		break;
	}
}

void Paddle::move(InputHandler::Message msg) {
	sf::Vector2f newPos;
	switch (msg) {
	case InputHandler::Message::PLAYER_MOVE_UP:
		newPos = model->getPosition().y <= BG_OUTLINE_THICKNESS ? model->getPosition() : model->getPosition() + sf::Vector2f(0, -speed);
		model->setPosition(newPos);
		break;
	case InputHandler::Message::PLAYER_MOVE_DOWN:
		newPos = model->getPosition().y >= (SCREEN_Y - BG_OUTLINE_THICKNESS - PHEIGHT) ? model->getPosition() : model->getPosition() + sf::Vector2f(0, speed);
		model->setPosition(newPos);
		break;
	}
}

void Paddle::setPlayer() {
	isPlayer = true;
}