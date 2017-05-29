#pragma once
#include "Player.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Player_states.h"


Player::Player(int x, int y, int control) : Movable_object() {
	type = PLAYER;
	pos_x = 1305;
	pos_y = 75;
	score = 0;
	width = 50;
	height = 160;
	acceleration = 3;

	jump_vel = 7;
	flip_right = true;
	fireball_cooldown = 0;
	hit_cooldown = 0;
	unkill_cooldown = 0;
	time_on_platform = -1;
	on_platform = false;

	controller = control;
	switch (controller) {
	case 0: gamepad = NULL; break;
	case 1: 
		gamepad = gamepad1;
		gamepad_id = SDL_JoystickInstanceID(joystick1);
		break;
	case 2: 
		gamepad = gamepad2; 
		gamepad_id = SDL_JoystickInstanceID(joystick2);
		break;
	}

	stand_animation = new Animated_texture(player_stand_texture, 8, -75, -40);
	//int order1[] = { 0, 1, 2, 1 };
	//stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player_run_texture, 13, -75, -40);
	run_animation->set_ticks_per_frame(13);
	jump_animation = new Animated_texture(player_jump_texture, 1, -75, -40);
	//jump_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	jump_animation->set_ticks_per_frame(25);
	hit_animation = new Animated_texture(player_hit_texture, 4, -44, -28);

	
	collision_box = { (int)pos_x, (int)pos_y, width, height };
	vulnerable = true;

	state = new Stand;
	state_stack.push(state);

	t_ball = NULL;
}

bool Player::kill() {
	if (vulnerable && unkill_cooldown == 0) {
		pos_x = 1305;
		pos_y = 75;
		player2->score += 1000;
		unkill_cooldown = game_time.get_ticks();
		return true;
	}
	return false;
}

Player::~Player() {
	delete texture;
	delete stand_animation;
	delete run_animation;
	delete jump_animation;
	delete hit_animation;
}

int Player::get_x() {
	return pos_x;
}

int Player::get_y() {
	return pos_y;
}

void Player::logic() {
	//printf("vel_x=%f; vel_y=%f\n", vel_x, vel_y);
	//printf("x=%f; y=%f\n", pos_x, pos_y);
	reduce_cooldowns();
	state_stack.top()->logic(*this);

	std::vector<Game_object*> collision_list;
	collision_list = get_collisions();
	bool on_plat = false;
	if (collision_list.size() != 0) {
		for (int i = 0; i < collision_list.size(); i++) {
			if (collision_list[i]->type == PLATFORM) {
				on_plat = true;
				break;
			}
		}
	}
	if (!on_plat) {
		on_platform = false;
	}
};

void Player::handle_events(SDL_Event& event) {
	state_stack.top()->handle_events(*this, event);
};

void Player::render() {
	state_stack.top()->render(*this);

	////Hit box rectangle
	//double scale = camera->get_scale();
	//SDL_Rect renderQuad = { (pos_x - camera->get_x()) * camera->get_scale(), (pos_y - camera->get_y()) * camera->get_scale(), width * scale, height * scale };
	////Outline of rectangle of texture
	//SDL_SetRenderDrawColor(main_renderer, 0, 255, 50, 100);
	//SDL_RenderDrawRect(main_renderer, &renderQuad);
}


void Player::reduce_cooldowns() {
	int time = game_time.get_ticks();
	if (time - fireball_cooldown >= 500) fireball_cooldown = 0;
	if (time - hit_cooldown >= 1000) hit_cooldown = 0;
	if (time - unkill_cooldown >= 1000) unkill_cooldown = 0;
}

void Player::teleport_to_ball() {
	double nx = t_ball->pos_x, ny = t_ball->pos_y;

	for (int i = 0; i <= width / 2; i++) {
		if (check_map_collision(nx + i, ny)) {
			nx = nx - width / 2 + i;
			break;
		}
		if (check_map_collision(nx - i, ny)) {
			nx = nx + width / 2 - i;
			break;
		}
	}
	for (int i = 0; i <= height / 2; i++) {
		if (check_map_collision(nx, ny + i)) {
			ny = ny - height / 2 + i;
			break;
		}
		if (check_map_collision(nx, ny - i)) {
			ny = ny + height / 2 - i;
			break;
		}
	}

	pos_x = nx - width / 2;
	pos_y = ny - height / 2;
}


