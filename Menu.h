#pragma once
#include "Programm_state.h"
#include <SDL.h>
#include "Texture.h"
#include "Menu_item.h"

class Menu : public Programm_state {
public:
	enum buttons {
		PLAY,
		OR,
		LEAVE,
	};
	Menu();
	~Menu();
	void handle_events();
	void logic();
	void render();
	int check_if_choosed();

private:
	SDL_Texture* background;
	Menu_item* items[10];

};

