#pragma once
#include <SDL.h>
#include "Texture.h"



class Menu_item {
public:
	Menu_item(int x, int y, SDL_Texture* item_texture);
	~Menu_item();
	void render();

	Texture* texture;
	SDL_Rect button_box;
	int pos_x, pos_y;
};

