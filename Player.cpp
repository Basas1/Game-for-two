#pragma once
#include "Player.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Player_states.h"
#include <math.h>

#define PI 3.14159265


Player::Player(int x, int y, int control) : Movable_object() {
	skip = 0;
	type = PLAYER;
	pos_x = 1305;
	pos_y = 75;
	score = 0;
	width = 50;
	height = 160;
	acceleration = 3;
	jump_vel = 7.5;
	flip_right = true;
	fireball_cooldown = 0;
	teleport_cooldown = 0;
	hit_cooldown = 0;
	unkill_cooldown = 0;
	time_on_platform = -1;
	on_platform = false;
	color_r = 50;
	color_g = 50;
	color_b = 255;

	controller = control;
	switch (controller) {
	case 0: 
		gamepad = NULL;
		gamepad_id = -1;
		break;
	case 1: 
		gamepad = gamepad1;
		gamepad_id = SDL_JoystickInstanceID(joystick1);
		break;
	case 2: 
		gamepad = gamepad2; 
		gamepad_id = SDL_JoystickInstanceID(joystick2);
		break;
	}

	for (int i = 0; i < 20; i++) {
		player_textures[i] = NULL;
	}
	int t_num = 0;

	stand_animation = new Animated_texture(player_stand_texture, 8, -75, -40);
	stand_animation->set_ticks_per_frame(25);
	player_textures[t_num++] = &stand_animation;
	run_animation = new Animated_texture(player_run_texture, 13, -75, -40);
	run_animation->set_ticks_per_frame(13);
	player_textures[t_num++] = &run_animation;
	jump_animation_rise = new Animated_texture(player_jump_rise_texture, 4, -75, -40);
	player_textures[t_num++] = &jump_animation_rise;
	jump_animation_fall = new Animated_texture(player_jump_fall_texture, 4, -75, -40);
	player_textures[t_num++] = &jump_animation_fall;
	jump_effect_animation1 = new Animated_texture(player_jump_effect_texture1, 5, -75, 120);
	jump_effect_animation1->set_ticks_per_frame(10);
	player_textures[t_num++] = &jump_effect_animation1;
	jump_effect_animation2 = new Animated_texture(player_jump_effect_texture2, 4, -75, 120);
	jump_effect_animation2->set_ticks_per_frame(10);
	player_textures[t_num++] = &jump_effect_animation2;
	hit_animation = new Animated_texture(player_hit_texture, 5, -75, -40);
	player_textures[t_num++] = &hit_animation;
	dive_animation = new Animated_texture(player_dive_texture, 1, -75, -40);
	player_textures[t_num++] = &dive_animation;
	dive_end_animation = new Animated_texture(blast_texture, 4, -100, -40);
	player_textures[t_num++] = &dive_end_animation;
	fireball_cast_animation1 = new Animated_texture(player_cast_fireball_texture1, 3, -60, 30);
	player_textures[t_num++] = &fireball_cast_animation1;
	fireball_cast_animation2 = new Animated_texture(player_cast_fireball_texture2, 9, -26, 30);
	fireball_cast_animation2->set_ticks_per_frame(2);
	player_textures[t_num++] = &fireball_cast_animation2;
	texture_color_toggled = false;

	arrow = new Animated_texture(arrow_texture, 1);
	arrow->set_�olor(color_r, color_g, color_b);

	mark = new Animated_texture(player_mark_texture, 1);

	collision_box = { (int)pos_x, (int)pos_y, width, height };
	vulnerable = true;

	state = new Stand;
	state_stack.push(state);

	t_ball = NULL;
}

bool Player::kill() {
	if (vulnerable && unkill_cooldown == 0) {
		if (t_ball != NULL) {
			if (t_ball->exist) {
				t_ball->kill();
				t_ball->blast();
				t_ball = NULL;
			}
		}
		pos_x = 1305;
		pos_y = 75;
		player2->score += 2500;
		unkill_cooldown = game_time.get_ticks();
		return true;
	}
	return false;
}

Player::~Player() {
	//delete texture;
	//delete stand_animation;
	//delete run_animation;
	//delete jump_animation_rise;
	//delete jump_animation_fall;
	//delete hit_animation;
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

	//If a key was pressed
	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		if (event.cbutton.which == gamepad_id) {
			switch (event.jbutton.button) {
			case 8: {
				bool already_exist = false;
				for (int i = 0; i < static_objects.size(); i++) {
					if (static_objects[i]->is_exist()) {
						if (static_objects[i]->type == HELP) {
							if (static_objects[i]->parent == this) {
								already_exist = true;
								static_objects[i]->exist = false;
								break;
							}
						}
					}
				}
				if (!already_exist) {
					Help* help;
					help = new Help(this);
					static_objects.insert(static_objects.end(), help);
				}
				break;
			}
			}
		}
	}
};

void Player::render() {

	if (unkill_cooldown != 0) {
		if (skip % 25 == 0) {
			skip = 0;
			toggle_texture_color();
			skip++;
		}
		else {
			skip++;
		}
	}
	else if (texture_color_toggled) {
		toggle_texture_color();
	}

	state_stack.top()->render(*this);
	
	//Arrow rendering
	if (t_ball != NULL) {
		double dist_y, dist_x;
		double param, result;
		dist_y = t_ball->pos_y - (pos_y + height / 3);
		dist_x = t_ball->pos_x - (pos_x + width / 2);
		param = dist_y / dist_x;
		result = atan(param) * 180 / PI;
		if (dist_x < 0) {
			result += 180;
		}
		arrow->render(pos_x + width / 2 - 125, pos_y + height / 2 - 125, true, result);

	}

	mark->render(pos_x, pos_y - mark->height * 3 / 2 );

	////Hit box rectangle
	//double scale = camera->get_scale();
	//SDL_Rect renderQuad = { (pos_x - camera->get_x()) * camera->get_scale(), (pos_y - camera->get_y()) * camera->get_scale(), width * scale, height * scale };
	////Outline of rectangle of texture
	//SDL_SetRenderDrawColor(main_renderer, 0, 255, 50, 100);
	//SDL_RenderDrawRect(main_renderer, &renderQuad);
}


void Player::reduce_cooldowns() {
	int time = game_time.get_ticks();
	if (time - fireball_cooldown >= 750) fireball_cooldown = 0;
	if (time - teleport_cooldown >= 500) teleport_cooldown = 0;
	if (time - hit_cooldown >= 1000) hit_cooldown = 0;
	if (time - unkill_cooldown >= 2000) {
		unkill_cooldown = 0;
	}
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

void Player::toggle_texture_color() {
	if (!texture_color_toggled) {
		for (int i = 0; i < 20; i++) {
			if (player_textures[i] != NULL) {
				Animated_texture* temp;
				temp = *player_textures[i];
				temp->set_�olor(color_r, color_g, color_b);
			}
		}
		texture_color_toggled = true;
	}
	else {
		for (int i = 0; i < 20; i++) {
			if (player_textures[i] != NULL) {
				Animated_texture* temp;
				temp = *player_textures[i];
				temp->set_�olor(255, 255, 255);
			}
		}
		texture_color_toggled = false;
	}
}


