#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, int side) : Movable_object() {
	type = FIREBALL;
	int start_speed = acceleration * 3;
	width = 14;
	height = 14;
	pos_x = x;
	pos_y = y;
	gravity = 0.005;
	vel_x = 0;
	vel_y = 0;
	exist = true;

	switch (side) {
	case RIGHT: {
		pos_x = x + 5;
		vel_x = start_speed;
		vel_y = -0.5;
		break;
	}
	case LEFT: {
		pos_x = x - width - 5;
		vel_x = -start_speed;
		vel_y = -0.5;
		break;
	}
	case UP: {
		pos_y = y - height - 5;
		vel_y = -start_speed;
		break;
	}
	case DOWN: {
		pos_y = y + height + 5;
		vel_y = start_speed;
		break;
	}
	case UP_RIGHT: {
		pos_y = y - height - 5;
		pos_x = x + 5;
		vel_x = start_speed;
		vel_y = -start_speed;
		break;
	}
	case UP_LEFT: {
		pos_y = y - height - 5;
		pos_x = x - width - 5;
		vel_x = -start_speed;
		vel_y = -start_speed;
		break;
	}
	case DOWN_RIGHT: {
		pos_y = y + height + 5;
		pos_x = x + 5;
		vel_x = start_speed;
		vel_y = start_speed;
		break;
	}
	case DOWN_LEFT: {
		pos_y = y + height + 5;
		pos_x = x - width - 5;
		vel_x = -start_speed;
		vel_y = start_speed;
		break;
	}
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
			if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
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
