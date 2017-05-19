#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, bool right) : Movable_object() {
	width = 50;
	height = 50;
	pos_x = x;
	pos_y = y;
	can_rise = 0;
	gravity = 0.005;
	vel_y = -0.5; 
	exist = true;
	if (right) {
		vel_x = acceleration * 3;
	}
	else {
		vel_x = -acceleration * 3;
	}

	fireball_animation = new Animated_texture(fireball_texture, 3);
	fireball_animation->set_clips();
	fireball_animation->set_width(width);
	fireball_animation->set_height(height);

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Fireball::move() {
	if (check_map_collision_all()) {
			exist = false;
			delete fireball_animation;
			fireball_animation = NULL;
	}
	if (exist) Movable_object::move();
}

void Fireball::logic() {
	move();
}

void Fireball::render() {
	fireball_animation->render(pos_x, pos_y);
	fireball_animation->next_frame();
}

Fireball::~Fireball() {
	delete fireball_animation;
}
