#include "stdafx.h"
#include "InputHandler.h"
#include "World.h"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		World::getInstance()->sendMessage(GAME_EXIT);
		World::getInstance()->getWindow()->close();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		World::getInstance()->sendMessage(PLAYER_MOVE_DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		World::getInstance()->sendMessage(PLAYER_MOVE_UP);
	}
	else {
		World::getInstance()->sendMessage(PLAYER_SLOW);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		World::getInstance()->sendMessage(LAUNCH);
	}
}