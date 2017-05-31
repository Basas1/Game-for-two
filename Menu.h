#pragma once
#include "Programm_state.h"
#include <SDL.h>
#include "Texture.h"

class Menu : public Programm_state {
public:
	Menu();
	~Menu();
	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
	Texture* play;
	Texture* or;
	Texture* leave;

	Texture* textures[10];

};

