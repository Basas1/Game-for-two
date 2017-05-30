#pragma once
#include "Player2.h"
#include "media.h"
#include "init.h"
#include "Player_states.h"



Player2::Player2(int x, int y, int control) : Player() {
	pos_x = 2600;
	pos_y = 75;
	flip_right = false;



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

	stand_animation = new Animated_texture(player2_stand_texture, 8, -75, -40);
	//int order1[] = { 0, 1, 2, 1 };
	//stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player2_run_texture, 13, -75, -40);
	run_animation->set_ticks_per_frame(13);
	jump_animation_rise = new Animated_texture(player_jump_rise_texture, 4, -75, -40);
	jump_animation_fall = new Animated_texture(player_jump_fall_texture, 4, -75, -40);
	hit_animation = new Animated_texture(player2_hit_texture, 4, -44, -28);
	dive_animation = new Animated_texture(player2_dive_texture, 1, -75, -40);


	type = PLAYER;
	width = 50;
	height = 160;
	score = 0;
	jump_vel = 7;
	fireball_cooldown = 0;
	hit_cooldown = 0;
	unkill_cooldown = 0;
	time_on_platform = -1;
	on_platform = false;
	acceleration = 3;

	collision_box = { (int)pos_x, (int)pos_y, width, height };

	state = new Stand;
	state_stack.push(state);

	t_ball = NULL;
}


Player2::~Player2() {
	delete texture;
	delete stand_animation;
	delete run_animation;
	delete jump_animation_rise;
	delete jump_animation_fall;
	delete hit_animation;
}


bool Player2::kill() {
	if (vulnerable && unkill_cooldown == 0) {
		pos_x = 2600;
		pos_y = 75;
		player1->score += 1000;
		unkill_cooldown = game_time.get_ticks();
		return true;
	}
	return false;
}

