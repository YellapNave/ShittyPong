#include "stdafx.h"
#include "World.h"

// initialize the world for the first time, return the World otherwise
World* World::getInstance() {
	if (!worldExists) {
		instance = new World();
		worldExists = true;
	}
	return instance;
}

World* World::instance = NULL;
bool World::worldExists = false;

World::World() {}

// initialize objects needed to render properly
void World::start() {
	// initialize the background object
	bg = new sf::RectangleShape();
	bg->setSize(sf::Vector2f(SCREEN_X - (2 * BG_OUTLINE_THICKNESS), SCREEN_Y - (2 * BG_OUTLINE_THICKNESS)));
	bg->setPosition(BG_OUTLINE_THICKNESS, BG_OUTLINE_THICKNESS);
	bg->setFillColor(sf::Color::Black);
	bg->setOutlineColor(sf::Color::Cyan);
	bg->setOutlineThickness(BG_OUTLINE_THICKNESS);

	// initialize font for scoring
	font = new sf::Font();
	if (!font->loadFromFile("space.ttf"))
		std::cout << "FONT NOT LOADED" << std::endl;
	else std::cout << "FONT LOADED" << std::endl;

	// set up scoreboard
	scoreboard = new sf::Text();
	scoreboard->setFont(*font);
	scoreboard->setCharacterSize(120);
	scoreboard->setPosition(SCREEN_X / 4, SCREEN_Y / 5);
	scoreboard->setFillColor(sf::Color::Cyan);
	scoreboard->setString("score: " + std::to_string(enemyScore) + " " + std::to_string(playerScore));

	// initialize the main renderwindow
	myWindow = new sf::RenderWindow(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shitty Pong", sf::Style::Fullscreen);
}

// update all gameobjects stored in world
void World::update() {
	std::list<GameObject*>::reverse_iterator iterator = objects.rbegin();
	for (; iterator != objects.rend(); iterator++) {
		(*iterator)->update();
	}
}

// clear, render background, render scoreboard, render all models, then display 
void World::render() {
	myWindow->clear();
	myWindow->draw(*bg);
	myWindow->draw(*scoreboard);
	std::list<GameObject*>::reverse_iterator iterator = objects.rbegin();
	for (; iterator != objects.rend(); iterator++) {
		sf::RectangleShape * model = (*iterator)->getModel();
		if (model != NULL)
			myWindow->draw(*model);
	}
	myWindow->display();
}

// send a 'game event' message to all gameobjects
void World::sendMessage(InputHandler::Message msg) {
	switch (msg) { // check if the message is a score
	case InputHandler::Message::SCORE_PLAYER:
		std::cout << "SCORE_PLAYER" << std::endl;
		score(PLAYER);
		break;
	case InputHandler::Message::SCORE_ENEMY:
		std::cout << "SCORE_ENEMY" << std::endl;
		score(ENEMY);
		break;
	}

	std::list<GameObject*>::reverse_iterator iterator = objects.rbegin();
	for (; iterator != objects.rend(); iterator++) {
		(*iterator)->receiveMessage(msg);
		switch (msg) {
		case InputHandler::Message::PLAYER_MOVE_UP: 
			std::cout << "PLAYER_MOVE_UP" << std::endl;
			break;
		case InputHandler::Message::PLAYER_MOVE_DOWN:
			std::cout << "PLAYER_MOVE_DOWN" << std::endl;
			break;
		case InputHandler::Message::PLAYER_SLOW:
			std::cout << "PLAYER_SLOW" << std::endl;
			break;
		case InputHandler::Message::GAME_EXIT:
			std::cout << "GAME_EXIT" << std::endl;
			break;
		}
	}
}

// add a gameobject to the list of objects in the world
void World::insertGameObject(GameObject* obj) {
	objects.push_back(obj);
}

// remove a gameobject from the list of objects in the world
void World::removeGameObject(GameObject* obj) {
	objects.remove(obj);
}

// get the main renderwindow
sf::RenderWindow* World::getWindow() {
	return myWindow;
}

GameObject* World::getObject(Object obj) {
	switch (obj) {
	case PLAYER:
		return player;
		break;
	case ENEMY:
		return enemy;
		break;
	case BALL:
		return ball;
	}
}

void World::setObject(Object obj, GameObject* p) {
	switch (obj) {
	case PLAYER:
		player = p;
		break;
	case ENEMY:
		enemy = p;
		break;
	case BALL:
		ball = p;
		break;
	}
}

void World::score(Object obj) {
	switch (obj) {
	case World::Object::PLAYER:
		bg->setFillColor(sf::Color::Blue);
		render();
		Sleep(500);
		playerScore++;
		bg->setFillColor(sf::Color::Black);
		break;
	case World::Object::ENEMY:
		bg->setFillColor(sf::Color::White);
		render();
		Sleep(500);
		enemyScore++;
		bg->setFillColor(sf::Color::Black);
	}
	scoreboard->setString("score: " + std::to_string(enemyScore) + " " + std::to_string(playerScore));
}