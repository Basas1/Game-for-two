#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, bool right) : Movable_object() {
	type = FIREBALL;
	width = 14;
	height = 14;
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

	fireball_animation = new Animated_texture(fireball_texture, 3, -25, -25);
	fireball_animation->set_clips();

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
	//Set rendering space
	double scale = camera->get_scale();
	SDL_Rect renderQuad = { (pos_x - camera->get_x()) * camera->get_scale(), (pos_y - camera->get_y()) * camera->get_scale(), width * scale, height * scale };

	fireball_animation->render(pos_x, pos_y);
	fireball_animation->next_frame();

	//Outline of rectangle of texture
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 100);
	SDL_RenderDrawRect(main_renderer, &renderQuad);
}

Fireball::~Fireball() {
	delete fireball_animation;
	fireball_animation = NULL;
}
