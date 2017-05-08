#include "Programm_state.h"
#include <SDL.h>
#pragma once
class Menu : public Programm_state {
public:
	Menu();
	~Menu();
	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
};

