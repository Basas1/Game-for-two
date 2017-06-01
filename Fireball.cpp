#pragma once
#include "Fireball.h"
#include "media.h"



Fireball::Fireball(int x, int y, int side, Game_object* p) : Movable_object() {
	type = FIREBALL;
	parent = p;
	int start_speed = acceleration * 4;
	width = 14;
	height = 14;
	pos_x = x;
	pos_y = y;
	gravity = 0;
	vel_x = 0;
	vel_y = 0;
	exist = true;
	last_trail = NULL;

	switch (side) {
	case RIGHT: {
		pos_x = x + 5;
		vel_x = start_speed;
		vel_y = 0;
		break;
	}
	case LEFT: {
		pos_x = x - width - 5;
		vel_x = -start_speed;
		vel_y = 0;
		break;
	}
	case UP: {
		pos_y = y - height - 5;
		vel_y = -start_speed;
		break;
	}
	case DOWN: {
		pos_y = y + height + 1;
		vel_y = start_speed;
		break;
	}
	case UP_RIGHT: {
		pos_y = y - height - 5;
		pos_x = x + 5;
		vel_x = start_speed * 7 / 10;
		vel_y = -start_speed * 7 / 10;
		break;
	}
	case UP_LEFT: {
		pos_y = y - height - 5;
		pos_x = x - width - 5;
		vel_x = -start_speed * 7 / 10;
		vel_y = -start_speed * 7 / 10;
		break;
	}
	case DOWN_RIGHT: {
		pos_y = y + height + 1;
		pos_x = x + 5;
		vel_x = start_speed * 7 / 10;
		vel_y = start_speed * 7 / 10;
		break;
	}
	case DOWN_LEFT: {
		pos_y = y + height + 1;
		pos_x = x - width - 5;
		vel_x = -start_speed * 7 / 10;
		vel_y = start_speed * 7 / 10;
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
		//delete this;
	}
	if (exist) Movable_object::move();
}

void Fireball::logic() {
	std::vector<Game_object*> collisions;
	collisions = get_collisions();
	if (collisions.size() != 0) {
		for (int i = 0; i < collisions.size(); i++) {
			if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER && collisions[i]!=parent) {
				if (collisions[i]->kill()) {
					exist = false; 
					//delete this;
				}
			}
		}
	}
	if (exist) {
		if (last_trail == NULL) {
			Fireball_trail* trail;
			trail = new Fireball_trail(pos_x, pos_y);
			last_trail = trail;
			//objects.insert(objects.end(), trail);
			static_objects.insert(static_objects.end(), trail);
		}
		else {
			//if (last_trail->f_trail->get_frame_number() != last_trail->f_trail->total_frames - 1) {
			if (last_trail->f_trail->get_frame_number() != 0) {
				Fireball_trail* trail;
				trail = new Fireball_trail(pos_x, pos_y);
				last_trail = trail;
				//objects.insert(objects.end(), trail);
				static_objects.insert(static_objects.end(), trail);
			}
		}

		//if (skip % 1 == 0) {
		//	skip = 0;
		//	Fireball_trail* trail;
		//	trail = new Fireball_trail(pos_x, pos_y);
		//	objects.insert(objects.end(), trail);
		//	//static_objects.insert(static_objects.end(), trail);
		//	skip++;
		//}
		//else {
		//	skip++;
		//}
	}
	move();
}

void Fireball::render() {
	fireball_animation->render(pos_x, pos_y);
	fireball_animation->next_frame();

	////Set rendering space
	//double scale = camera->get_scale();
	//SDL_Rect renderQuad = { (pos_x - camera->get_x()) * camera->get_scale(), (pos_y - camera->get_y()) * camera->get_scale(), width * scale, height * scale };
	//Outline of rectangle of texture
	//SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 100);
	//SDL_RenderDrawRect(main_renderer, &renderQuad);
}

void Fireball::reverse() {
	vel_x = -vel_x;
	vel_y = -vel_y;
}


Fireball::~Fireball() {
	delete fireball_animation;
	fireball_animation = NULL;
}
