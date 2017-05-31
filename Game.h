#pragma once
#include "Programm_state.h"
#include "Game_object.h"
#include "Static_object.h"
#include <SDL.h>
#include "Player.h"
#include "Player2.h"


class Game : public Programm_state {
public:
	Game();
	~Game();
	void handle_events();
	void logic();
	void render();
	void toggle();
	void pause_game();

private:
	SDL_Texture* background;
	SDL_Texture* background2;
	Capture_platform* platform;
};

