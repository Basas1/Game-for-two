#pragma once
#include "Fireball.h"
#include "media.h"

#define PI 3.14159265


Fireball::Fireball(int x, int y, int side, Player* p) : Movable_object() {
	type = FIREBALL;
	parent = p;
	player = p;
	int start_speed = acceleration * 4;
	width = 14;
	height = 14;
	pos_x = x;
	pos_y = y;
	gravity = 0;
	can_rise = 0;
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

	angle = get_angle();

	p1_fireball_animation = player1->fireball;
	p2_fireball_animation = player2->fireball;

	if (parent == player1) {
		fireball_animation = p1_fireball_animation;
	}
	else {
		fireball_animation = p2_fireball_animation;
	}

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Fireball::move() {
	if (exist) {
		if (Movable_object::move()) {
			exist = false;
		}
	}
}

void Fireball::logic() {
	if (parent == player1) {
		fireball_animation = p1_fireball_animation;
		player = player1;
	}
	else if (parent == player2) {
		fireball_animation = p2_fireball_animation;
		player = player2;
	}
	angle = get_angle();
	std::vector<Game_object*> collisions;
	collisions = get_collisions();
	if (collisions.size() != 0) {
		for (int i = 0; i < collisions.size(); i++) {
			if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER && collisions[i]!=parent) {
				if (collisions[i]->kill()) {
					exist = false; 
				}
			}
		}
	}
	if (exist) {
		if (last_trail == NULL) {
			Fireball_trail* trail;
			trail = new Fireball_trail(pos_x, pos_y, player, angle);
			last_trail = trail;
			//objects.insert(objects.end(), trail);
			static_objects.insert(static_objects.end(), trail);
		}
		else {
			//if (last_trail->f_trail->get_frame_number() != last_trail->f_trail->total_frames - 1) {
			//if (last_trail->f_trail->get_frame_number() != 0) {
			if (last_trail->frame != 0) {
				Fireball_trail* trail;
				trail = new Fireball_trail(pos_x, pos_y, player, angle);
				last_trail = trail;
				//objects.insert(objects.end(), trail);
				static_objects.insert(static_objects.end(), trail);
			}
		}
	}
	move();
}

void Fireball::render() {
	fireball_animation->render(pos_x, pos_y, true, angle);
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

double Fireball::get_angle() {
	double x1, x2, y1, y2;
	x1 = pos_x;
	x2 = pos_x + vel_x;
	y1 = pos_y;
	y2 = pos_y + vel_y;
	double dist_y, dist_x;
	double param, result;
	dist_x = x2 - x1;
	dist_y = y2 - y1;
	param = dist_y / dist_x;
	result = atan(param) * 180 / PI;
	if (dist_x < 0) {
		result += 180;
	}
	return result;
}