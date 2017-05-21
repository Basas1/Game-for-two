#include "Teleport_ball.h"
#include "media.h"



Teleport_ball::Teleport_ball(int x, int y, bool right) : Movable_object() {
	type = TELEPORT;
	width = 0;
	height = 0;
	pos_y = y;
	can_rise = 0;
	gravity = 0;
	vel_y = 0;
	exist = true;
	if (right) {
		pos_x = x + 5;
		vel_x = acceleration * 2;
	}
	else {
		pos_x = x - width - 5;
		vel_x = -acceleration * 2;
	}

	teleport_ball_animation = new Animated_texture(fireball_texture, 3, -32, -32);
	teleport_ball_animation->set_clips();
	teleport_ball_animation->set_ñolor(50, 50, 255);
	//teleport_ball_animation->set_width(1);
	//teleport_ball_animation->set_height(1);

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Teleport_ball::move() {
	int old_pos_x = pos_x;
	int old_pos_y = pos_y;

	if (vel_x > 0) {
		for (pos_x; pos_x <= old_pos_x + vel_x; pos_x++) {
			if (check_map_collision(pos_x + 1, pos_y) && check_map_collision(pos_x, pos_y + 1)) {
				vel_y = -abs(vel_x);
				vel_x = 0;
				break;
			} else if (check_map_collision(pos_x + 1, pos_y) && check_map_collision(pos_x, pos_y - 1)) {
				vel_y = abs(vel_x);
				vel_x = 0;
				break;
			}
			if (check_map_collision(pos_x + 1,pos_y)) {
				vel_x = -vel_x;
				break;
			}
		}
	}
	else if (vel_x < 0 ){
		for (pos_x; pos_x >= old_pos_x + vel_x; pos_x--) {
			if (check_map_collision(pos_x - 1, pos_y) && check_map_collision(pos_x, pos_y + 1)) {
				vel_y = -abs(vel_x);
				vel_x = 0;
				break;
			} else if (check_map_collision(pos_x - 1, pos_y) && check_map_collision(pos_x, pos_y - 1)) {
				vel_y = abs(vel_x);
				vel_x = 0;
				break;
			}
			if (check_map_collision(pos_x - 1, pos_y)) {
				vel_x = -vel_x;
				break;
			}
		}
	}
	else if (vel_y > 0) {
		for (pos_y; pos_y <= old_pos_y + vel_y; pos_y++) {
			if (check_map_collision(pos_x, pos_y + 1) && check_map_collision(pos_x + 1, pos_y)) {
				vel_x = -abs(vel_y);
				vel_y = 0;
				break;
			} else if (check_map_collision(pos_x, pos_y + 1) && check_map_collision(pos_x - 1, pos_y)) {
				vel_x = abs(vel_y);
				vel_y = 0;
				break;
			}

			if (check_map_collision(pos_x, pos_y + 1)) {
				vel_y = -vel_y;
				break;
			}
		}
	}
	else if (vel_y < 0) {
		for (pos_y; pos_y >= old_pos_y + vel_y; pos_y--) {
			if (check_map_collision(pos_x, pos_y - 1) && check_map_collision(pos_x + 1, pos_y)) {
				vel_x = -abs(vel_y);
				vel_y = 0;
				break;
			} else if (check_map_collision(pos_x, pos_y - 1) && check_map_collision(pos_x - 1, pos_y)) {
				vel_x = abs(vel_y);
				vel_y = 0;
				break;
			}
			if (check_map_collision(pos_x, pos_y - 1)) {
				vel_y = -vel_y;
				break;
			}
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
