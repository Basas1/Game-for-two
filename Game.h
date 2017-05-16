#pragma once
#include "Programm_state.h"
#include "Game_object.h"
#include <SDL.h>
#include "Player.h"


class Game : public Programm_state {
public:
	Game();
	~Game();
	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
	Player* player;
};

