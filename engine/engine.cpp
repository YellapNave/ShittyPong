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
sf::RectangleShape* getbg();
Paddle* getPlayer();
Paddle* getEnemy();
Ball* getBall();

int main(int argc, char** argv)
{
	World::getInstance()->start();

	Paddle* player = getPlayer();
	Paddle* enemy = getEnemy();
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


Paddle* getPlayer() {
	Paddle* player = new Paddle();
	player->start(PWIDTH, PHEIGHT, PLAYER_START);
	player->setPlayer();
	return player;
}

Paddle* getEnemy() {
	Paddle* enemy = new Paddle();
	enemy->start(PWIDTH, PHEIGHT, ENEMY_START);
	return enemy;
}


Ball* getBall() {
	Ball* ball = new Ball();
	ball->start();
	return ball;
}