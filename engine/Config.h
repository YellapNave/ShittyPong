#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

static sf::Time MS_PER_UPDATE = sf::milliseconds(17);
static float SCALE = MS_PER_UPDATE.asSeconds();
static int SCREEN_X = 1920;
static int SCREEN_Y = 1080;
static int PWIDTH = SCREEN_X*0.01;
static int PHEIGHT = SCREEN_Y*0.2;
static int BALL_SIZE = 20;
static int BG_OUTLINE_THICKNESS = 15;
static sf::Vector2f PLAYER_START = sf::Vector2f(SCREEN_X*0.95 - PWIDTH, SCREEN_Y*0.45);
static sf::Vector2f ENEMY_START = sf::Vector2f(SCREEN_X*0.05, SCREEN_Y*0.45);
static sf::Vector2f BALL_START = PLAYER_START + sf::Vector2f(-12, PHEIGHT*0.5 - 4);