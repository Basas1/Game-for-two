#include "Menu_item.h"



Menu_item::Menu_item(int button_type, int x, int y, SDL_Texture* item_texture, bool can_choose) {
	type = button_type;
	pos_x = x;
	pos_y = y;
	choosable = can_choose;
	choosen = false;

	texture = new Texture(item_texture);
	texture->set_absolute_coord();

	width = texture->width;
	height = texture->height;

	button_box = { x, y, width, height };

}

void Menu_item::toggle() {
	if (choosable) {
		if (!choosen) {
			choosen = true;
			texture->set_ñolor(128, 255, 255);
		}
		else {
			choosen = false;
			texture->set_ñolor(255, 255, 255);
		}
	}
}


Menu_item::~Menu_item() {
	delete texture;
	texture = NULL;
}

void Menu_item::render() {
	texture->render(pos_x, pos_y);
}

void Menu_item::set_x(int x) {
	pos_x = x;
}

void Menu_item::set_y(int y) {
	pos_y = y;
}

