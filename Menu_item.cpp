#include "Menu_item.h"



Menu_item::Menu_item(int x, int y, SDL_Texture* item_texture) {
	pos_x = x;
	pos_y = y;

	texture = new Texture(item_texture);

	button_box = { x, y, texture->width, texture->height };

}


Menu_item::~Menu_item() {
	delete texture;
	texture = NULL;
}

void Menu_item::render() {
	texture->render(pos_x, pos_y);
}

