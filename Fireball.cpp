#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, bool left) : Movable_object() {
	width = 50;
	height = 50;
	pos_x = x;
	pos_y = y;
	can_rise = 0;
	gravity = 0.05;
	vel_y = -4;

	exist = true;
	if (left) {
		vel_x = -acceleration * 2;
	}
	else {
		vel_x = acceleration * 2;
	}

	texture = new Texture(fireball_texture);
	texture->set_width(width);
	texture->set_height(height);

	collision_box = { pos_x, pos_y, width, height };
}

void Fireball::move() {
	if (check_map_collision_all()) {
		exist = false;
	}
	if (exist) Movable_object::move();
}

void Fireball::render() {
	if (exist) texture->render(pos_x, pos_y);
}

Fireball::~Fireball() {
	delete texture;
}
