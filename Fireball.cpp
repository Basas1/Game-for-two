#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, bool right) : Movable_object() {
	type = FIREBALL;
	width = 50;
	height = 50;
	pos_y = y;
	can_rise = 0;
	gravity = 0.005;
	vel_y = -0.5; 
	exist = true;
	if (right) {
		pos_x = x + 5;
		vel_x = acceleration * 3;
	}
	else {
		pos_x = x - width - 5;
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
	}
	if (exist) Movable_object::move();
}

void Fireball::logic() {
	std::vector<Game_object*> collisions;
	collisions = get_collisions();
	if (collisions.size() != 0) {
		for (int i = 0; i < collisions.size(); i++) {
			if (collisions[i]->type == ENEMY) {
				collisions[i]->kill();
				exist = false;
			}
		}
	}
	move();
}

void Fireball::render() {
	fireball_animation->render(pos_x, pos_y);
	fireball_animation->next_frame();
}

Fireball::~Fireball() {
	delete fireball_animation;
	fireball_animation = NULL;
}
