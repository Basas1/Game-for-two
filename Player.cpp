#include "Player.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Player_states.h"


Player::Player() : Movable_object() {
	width = 40;
	height = 128;
	pos_x = 50;
	pos_y = 1500;
	jump_vel = 7;
	flip_right = true;

	stand_animation = new Animated_texture(player_stand_texture, 3);
	int order1[] = { 0, 1, 2, 1 };
	stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player_run_texture, 10);
	jump_animation = new Animated_texture(player_jump_texture, 3);
	jump_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	jump_animation->set_ticks_per_frame(25);
	hit_animation = new Animated_texture(player_hit_texture, 4);
	int order2[] = { 0, 1, 2, 3, 1 };
	hit_animation->set_frame_order(order2, sizeof(order2) / sizeof(int));

	//stand_animation = new Animated_texture(player_stand_texture, 12);
	//run_animation = new Animated_texture(player_run_texture, 4);
	//jump_animation = new Animated_texture(player_jump_texture, 4);
	//stand_animation->set_height(height);
	////stand_animation->set_width(width);
	//run_animation->set_height(height);
	////run_animation->set_width(width);
	//jump_animation->set_height(height);
	////jump_animation->set_width(width);

	//int order[] = { 1, 2, 3 };
	//jump_animation->set_frame_order(order, sizeof(order) / sizeof(int));
	//run_animation->set_frame_order(order, sizeof(order) / sizeof(int));
	//jump_animation->set_ticks_per_frame(30);
	//run_animation->set_ticks_per_frame(30);




	collision_box = { (int)pos_x, (int)pos_y, width, height };
	center_x = width / 2;
	center_y = height / 2;

	state = new Stand;
	state_stack.push(state);
}

Player::~Player() {
	delete texture;
	delete run_animation;
}

int Player::round(float f) {
	return (f > 0.0) ? (f + 0.5) : (f - 0.5);
}

int Player::get_x() {
	center_x = pos_x + width / 2;
	return center_x;
}

int Player::get_y() {
	center_y = pos_y + height / 2;
	return center_y;
}

void Player::logic() {
	printf("vel_x=%f\n", vel_x);
	state_stack.top()->logic(*this);
};

void Player::handle_events(SDL_Event& event) {
	state_stack.top()->handle_events(*this, event);
};

void Player::render() {
	center_x = pos_x + width / 2;
	center_y = pos_y + height / 2;
	state_stack.top()->render(*this);
}
