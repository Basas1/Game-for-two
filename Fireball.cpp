#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, bool right) : Movable_object() {
	width = 14;
	height = 14;
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

	fireball_animation = new Animated_texture(fireball_texture, 3, -17, -17);
	fireball_animation->set_clips();

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
	//Set rendering space
	SDL_Rect renderQuad = { pos_x - camera->get_x(), pos_y - camera->get_y(), width, height };

	fireball_animation->render(pos_x, pos_y);
	fireball_animation->next_frame();

	//Outline of rectangle of texture
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(main_renderer, &renderQuad);
}

Fireball::~Fireball() {
	delete fireball_animation;
}
