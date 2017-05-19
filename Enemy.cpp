#include "Enemy.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Enemy_states.h"


Enemy::Enemy() {
	width = 40;
	height = 128;
	pos_x = 600;
	pos_y = 1500;
	flip_right = false;

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

	state = new E_Stand;
	state_stack.push(state);
}


Enemy::~Enemy() {
	delete texture;
	delete stand_animation;
	delete run_animation;
	delete jump_animation;
	delete hit_animation;
}


int Enemy::get_x() {
	return pos_x;
}

int Enemy::get_y() {
	return pos_y;
}

void Enemy::logic() {
	state_stack.top()->logic(*this);
	collision_box = { (int)pos_x, (int)pos_y, width, height };
};

void Enemy::render() {
	state_stack.top()->render(*this);
}

