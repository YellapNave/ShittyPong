#pragma once

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput();
	enum Message { GAME_EXIT, PLAYER_MOVE_UP, PLAYER_MOVE_DOWN, PLAYER_SLOW, ENEMY_MOVE_UP, ENEMY_MOVE_DOWN, ENEMY_SLOW, LAUNCH };
};

