#pragma once

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handleInput();
	enum Message { PLAYER_MOVE_UP, PLAYER_MOVE_DOWN, GAME_EXIT };
};

