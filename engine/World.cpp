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
	// initialize the physics world
	b2Vec2 gravity(0, 0);
	myWorld = new b2World(gravity);

	// initialize the background object
	bg = new sf::RectangleShape();
	bg->setSize(sf::Vector2f(SCREEN_X - (2 * BG_OUTLINE_THICKNESS), SCREEN_Y - (2 * BG_OUTLINE_THICKNESS)));
	bg->setPosition(BG_OUTLINE_THICKNESS, BG_OUTLINE_THICKNESS);
	bg->setFillColor(sf::Color::Black);
	bg->setOutlineColor(sf::Color::White);
	bg->setOutlineThickness(BG_OUTLINE_THICKNESS);

	// initialize the main renderwindow
	myWindow = new sf::RenderWindow(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shitty Pong", sf::Style::Fullscreen);
}

// update all gameobjects stored in world
void World::update() {
	std::list<GameObject*>::reverse_iterator iterator = objects.rbegin();
	for (; iterator != objects.rend(); iterator++) {
		(*iterator)->update();
		b2Vec2 pos = (*iterator)->getBody()->GetPosition();
		std::cout << pos.x << " " << pos.y << std::endl;
	}

	// step the physics world
	myWorld->Step(MS_PER_UPDATE.asSeconds(), VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

// clear, render background, render all models, then display 
void World::render() {
	myWindow->clear();
	myWindow->draw(*bg);

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
			// std::cout << "PLAYER_SLOW" << std::endl;
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

GameObject* World::getObj(Object obj) {
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

b2World* World::getCollWorld() {
	return myWorld;
}

void World::setObj(GameObject* p, Object obj) {
	switch (obj) {
	case PLAYER:
		player = p;
		break;
	case ENEMY:
		enemy = p;
		break;
	case BALL:
		ball = p;
	}
}

