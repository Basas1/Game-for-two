#pragma once
#include "Teleport_ball.h"
#include "media.h"
#include "init.h"
#include "Static_object.h"
#include "Player.h"


Teleport_ball::Teleport_ball(int x, int y, Player* p, int side) : Movable_object() {
	int start_speed = acceleration * 4;
	type = TELEPORT;
	parent = p;
	width = 0;
	height = 0;
	pos_x = x;
	pos_y = y;
	can_rise = 0;
	gravity = 0;
	vel_x = 0;
	vel_y = 0;
	exist = true;
	create_time = game_time.get_ticks();
	stage_two = false;

	switch (side) {
	case RIGHT: {
		vel_x = start_speed;
		break;
	}
	case LEFT: {
		vel_x = -start_speed;
		break;
	}
	case UP: {
		vel_y = -start_speed;
		break;
	}
	case DOWN: {
		vel_y = start_speed;
		break;
	}
	case UP_RIGHT: {
		vel_x = start_speed * 7 / 10;
		vel_y = -start_speed * 7 / 10;
		break;
	}
	case UP_LEFT: {
		vel_x = -start_speed * 7 / 10;
		vel_y = -start_speed * 7 / 10;
		break;
	}
	case DOWN_RIGHT: {
		vel_x = start_speed * 7 / 10;
		vel_y = start_speed * 7 / 10;
		break;
	}
	case DOWN_LEFT: {
		vel_x = -start_speed * 7 / 10;
		vel_y = start_speed * 7 / 10;
		break;
	}
	}

	//vel_x = 0;
	//vel_y = 0;

	teleport_ball_opening = p->tp_ball_opening;
	teleport_ball_opened = p->tp_ball_opened;
	teleport_ball_opening->reset();
	teleport_ball_opened->reset();
	b_width = 64;
	b_height = 64;
	blast_rad = 128;

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Teleport_ball::move() {
	double old_pos_x = pos_x;
	double old_pos_y = pos_y;
	int x_iter = 0;
	int y_iter = 0;

	if (vel_x < 0) x_iter = -1;
	if (vel_x > 0) x_iter = 1;
	if (vel_y < 0) y_iter = -1;
	if (vel_y > 0) y_iter = 1;

	for (pos_x, pos_y; old_pos_x + vel_x - pos_x != 0 || old_pos_y + vel_y - pos_y != 0; pos_x += x_iter, pos_y += y_iter) {
		if (check_map_collision(pos_x + x_iter, pos_y + y_iter)) {
			if (x_iter == 0) {
				if (check_map_collision(pos_x - 1, pos_y + y_iter) && check_map_collision(pos_x + 1, pos_y + y_iter)) {
					vel_y = -vel_y;
					break;
				}
				if (check_map_collision(pos_x - 1, pos_y + y_iter)) {
					vel_x = abs(vel_y);
					vel_y = 0;
					break;
				}
				else if (check_map_collision(pos_x + 1, pos_y + y_iter)) {
					vel_x = -abs(vel_y);
					vel_y = 0;
					break;
				}
			}
			if (y_iter == 0) {
				if (check_map_collision(pos_x + x_iter, pos_y - 1) && check_map_collision(pos_x + x_iter, pos_y + 1)) {
					vel_x = -vel_x;
					break;
				}
				if (check_map_collision(pos_x + x_iter, pos_y -1)) {
					vel_y = abs(vel_x);
					vel_x = 0;
					break;
				}
				else if (check_map_collision(pos_x + x_iter, pos_y + 1)) {
					vel_y = -abs(vel_x);
					vel_x = 0;
					break;
				}
			}

			if (check_map_collision(pos_x + x_iter, pos_y) && check_map_collision(pos_x, pos_y + y_iter)) {
				vel_x = -vel_x;
				vel_y = -vel_y;
				break;
			}
			if (check_map_collision(pos_x, pos_y + y_iter) || check_map_collision(pos_x + x_iter * 2, pos_y + y_iter) && (!check_map_collision(pos_x + x_iter, pos_y))) {
				vel_y = -vel_y;
				break;
			}
			if (check_map_collision(pos_x + x_iter, pos_y) || check_map_collision(pos_x + x_iter, pos_y + y_iter * 2) && (!check_map_collision(pos_x, pos_y + y_iter))) {
				vel_x = -vel_x;
				break;
			}
			vel_x = -vel_x;
			vel_y = -vel_y;
			break;
		}
	}
}


void Teleport_ball::logic() {
	if (!stage_two) {
		if (teleport_ball_opening->get_replay_count() > 0) {
			teleport_ball_opening->reset();
			teleport_ball_opened->reset();
			stage_two = true;
		}
	}
	else {
		//Create teleport trail
		if (exist) {
			if (last_trail == NULL) {
				Tp_ball_trail* trail;
				trail = new Tp_ball_trail(pos_x, pos_y, parent);
				last_trail = trail;
				static_objects.insert(static_objects.end(), trail);
			}
			else {
				if (last_trail->frame != 0) {
					Tp_ball_trail* trail;
					trail = new Tp_ball_trail(pos_x, pos_y, parent);
					last_trail = trail;
					static_objects.insert(static_objects.end(), trail);
				}
			}
		}
	}

	move();
}

void Teleport_ball::render() {
	if (stage_two) {
		teleport_ball_opened->render(pos_x, pos_y);
		teleport_ball_opened->next_frame();
	}
	else {
		teleport_ball_opening->render(pos_x, pos_y);
		teleport_ball_opening->next_frame();
	}
}

void Teleport_ball::blast() {
	Blast* blast;
	blast = new Blast((int)pos_x, (int)pos_y, parent);
	objects.insert(objects.end(), blast);
	Mix_PlayChannel(-1, teleport_blast_sound, 0);
}

