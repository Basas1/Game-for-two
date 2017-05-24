#pragma once
#include "Player2.h"
#include "media.h"
#include "init.h"
#include "Player_states.h"



Player2::Player2(int x, int y, int control) : Player() {
	type = PLAYER;
	width = 40;
	height = 100;
	pos_x = 2100;
	pos_y = 1100;

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


	jump_vel = 7;
	flip_right = false;
	fireball_cooldown = 0;


	stand_animation = new Animated_texture(player2_stand_texture, 3, -44, -28);
	int order1[] = { 0, 1, 2, 1 };
	stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player2_run_texture, 10, -44, -28);
	jump_animation = new Animated_texture(player2_jump_texture, 3, -44, -28);
	jump_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	jump_animation->set_ticks_per_frame(25);
	hit_animation = new Animated_texture(player2_hit_texture, 4, -44, -28);


	collision_box = { (int)pos_x, (int)pos_y, width, height };

	state = new Stand;
	state_stack.push(state);

	t_ball = NULL;
}


Player2::~Player2() {
	delete texture;
	delete stand_animation;
	delete run_animation;
	delete jump_animation;
	delete hit_animation;
}


void Player2::kill() {
	if (vulnerable) {
		pos_x = 2600;
		pos_y = 135;
	}
}

