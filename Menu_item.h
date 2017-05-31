#pragma once
#include <SDL.h>
#include "Texture.h"



class Menu_item {
public:
	Menu_item(int button_type, int x, int y, SDL_Texture* item_texture, bool can_choose=true);
	~Menu_item();
	void render();
	void set_x(int x);
	void set_y(int y);
	void toggle();
	

	Texture* texture;
	SDL_Rect button_box;
	int type;
	int pos_x, pos_y;
	int width;
	int height;
	bool choosable;
	bool choosen;
};

