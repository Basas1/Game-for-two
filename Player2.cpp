#pragma once
#include "Player2.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Player2_states.h"





Player2::Player2() {
	type = PLAYER;
	width = 40;
	height = 100;
	pos_x = 2100;
	pos_y = 1100;
	jump_vel = 7;
	flip_right = true;

	stand_animation = new Animated_texture(player2_stand_texture, 3, -44, -28);
	int order1[] = { 0, 1, 2, 1 };
	stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player2_run_texture, 10, -44, -28);
	jump_animation = new Animated_texture(player2_jump_texture, 3, -44, -28);
	jump_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	jump_animation->set_ticks_per_frame(25);
	hit_animation = new Animated_texture(player2_hit_texture, 8, -44, -28);


	collision_box = { (int)pos_x, (int)pos_y, width, height };

	state = new P2_Stand;
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


void Player2::logic() {
	//printf("x=%f; y=%f\n", pos_x, pos_y);
	state_stack.top()->logic(*this);

	std::vector<Game_object*> collision_list;
	collision_list = get_collisions();
	//printf("count=%d;\n", collision_list.size());
};

void Player2::handle_events(SDL_Event& event) {
	state_stack.top()->handle_events(*this, event);
};


void Player2::render() {
	state_stack.top()->render(*this);

	//Hit box rectangle
	SDL_Rect renderQuad = { pos_x - camera->get_x(), pos_y - camera->get_y(), width, height };
	//Outline of rectangle of texture
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(main_renderer, &renderQuad);
}
