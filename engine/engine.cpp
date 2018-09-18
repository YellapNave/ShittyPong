// engine.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "World.h"
#include "GameObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "InputHandler.h"
#include "Config.h"

void gameLoop(sf::RenderWindow*);
void render();
void update();
Paddle* getPaddle(World::Object);
Ball* getBall();

int main(int argc, char** argv)
{
	World::getInstance()->start();

	Paddle* player = getPaddle(World::Object::PLAYER);
	Paddle* enemy = getPaddle(World::Object::ENEMY);
	Ball* ball = getBall();

	gameLoop(World::getInstance()->getWindow());
}

void gameLoop(sf::RenderWindow* window) {
	sf::Clock clock;
	sf::Time lag = sf::milliseconds(0);

	InputHandler* input = new InputHandler;

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}

		sf::Time elapsed = clock.getElapsedTime();
		lag += elapsed;
		clock.restart();
		
		while (lag >= MS_PER_UPDATE) {
			input->handleInput();
			update();
			lag -= MS_PER_UPDATE;
		}

		render();
	}
}

void render() {
	World::getInstance()->render();
}

void update() {
	World::getInstance()->update();
}

Paddle* getPaddle(World::Object type) {
	Paddle* paddle = new Paddle();

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;

	switch (type) {
	case World::Object::PLAYER:
		paddle->setPlayer();
		paddle->start(PWIDTH, PHEIGHT, PLAYER_START);
		bodyDef.position.Set(PLAYER_START.x / PIXELS_TO_METERS, PLAYER_START.y / PIXELS_TO_METERS);
		break;
	case World::Object::ENEMY:
		paddle->start(PWIDTH, PHEIGHT, ENEMY_START);
		bodyDef.position.Set(ENEMY_START.x / PIXELS_TO_METERS, ENEMY_START.y / PIXELS_TO_METERS);
	}

	b2Body* body = World::getInstance()->getCollWorld()->CreateBody(&bodyDef);
	paddle->setBody(body);

	World::getInstance()->setObj(paddle, type);
	b2PolygonShape paddleShape;
	paddleShape.SetAsBox((PWIDTH / 2) / PIXELS_TO_METERS, (PHEIGHT / 2) / PIXELS_TO_METERS);
	body->CreateFixture(&paddleShape, 0);

	return paddle;
}

Ball* getBall() {
	Ball* ball = new Ball();
	ball->start();
	ball->getModel()->setPosition(World::getInstance()->getObj(World::Object::PLAYER)->getPosition() + sf::Vector2f(-BALL_SIZE - 12, PHEIGHT / 2 - BALL_SIZE / 2));
	World::getInstance()->setObj(ball, World::Object::BALL);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0;
	bodyDef.position.Set((BALL_START.x + BALL_SIZE / 2) / PIXELS_TO_METERS, (BALL_START.y - BALL_SIZE / 2) / PIXELS_TO_METERS);
	bodyDef.fixedRotation = true;
	b2Body* body = World::getInstance()->getCollWorld()->CreateBody(&bodyDef);
	ball->setBody(body);

	b2CircleShape ballShape;
	ballShape.m_p.Set((BALL_SIZE / 2) / PIXELS_TO_METERS, (BALL_SIZE / 2) / PIXELS_TO_METERS);
	ballShape.m_radius = BALL_SIZE / 2;
	body->CreateFixture(&ballShape, 0);

	return ball;
}