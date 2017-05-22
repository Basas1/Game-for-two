#pragma once
#include "Teleport_ball.h"
#include "media.h"
#include "init.h"



Teleport_ball::Teleport_ball(int x, int y, int side) : Movable_object() {
	int start_speed = acceleration * 2;
	type = TELEPORT;
	width = 0;
	height = 0;
	pos_x = x;
	pos_y = y;
	can_rise = 0;
	gravity = 0;
	vel_x = 0;
	vel_y = 0;
	exist = true;

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
		vel_x = start_speed;
		vel_y = -start_speed;
		break;
	}
	case UP_LEFT: {
		vel_x = -start_speed;
		vel_y = -start_speed;
		break;
	}
	case DOWN_RIGHT: {
		vel_x = start_speed;
		vel_y = start_speed;
		break;
	}
	case DOWN_LEFT: {
		vel_x = -start_speed;
		vel_y = start_speed;
		break;
	}

	}

	teleport_ball_animation = new Animated_texture(fireball_texture, 3, -32, -32);
	teleport_ball_animation->set_clips();
	teleport_ball_animation->set_�olor(50, 50, 255);

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

			if (check_map_collision(pos_x + x_iter, pos_y + y_iter - 2) && check_map_collision(pos_x + x_iter, pos_y + y_iter + 2)) {
				vel_x = -vel_x;
				break;
			}
			if (check_map_collision(pos_x + x_iter - 2, pos_y + y_iter) && check_map_collision(pos_x + x_iter + 2, pos_y + y_iter)) {
				vel_y = -vel_y;
				break;
			}
			vel_x = -vel_x;
			vel_y = -vel_y;
			break;
		}
	}
}


void Teleport_ball::logic() {
	move();
}

void Teleport_ball::render() {
	//Set rendering space
	SDL_Rect renderQuad = { pos_x - camera->get_x(), pos_y - camera->get_y(), width, height };

	teleport_ball_animation->render(pos_x, pos_y);
	teleport_ball_animation->next_frame();

	//Outline of rectangle of texture
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(main_renderer, &renderQuad);
}


Teleport_ball::~Teleport_ball() {
	delete teleport_ball_animation;
	teleport_ball_animation = NULL;
}