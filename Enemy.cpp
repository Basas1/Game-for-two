#include "Enemy.h"
#include "media.h"
#include "init.h"
#include "Fireball.h"
#include "Enemy_states.h"
#include "AI_states.h"


Enemy::Enemy() {
	//collidable = true;
	type = ENEMY;
	width = 40;
	height = 100;
	pos_x = 2700;
	pos_y = 1100;
	flip_right = false;

	stand_animation = new Animated_texture(player_stand_texture, 3, -44, -28);
	int order1[] = { 0, 1, 2, 1 };
	stand_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player_run_texture, 10, -44, -28);
	jump_animation = new Animated_texture(player_jump_rise_texture, 3, -44, -28);
	jump_animation->set_frame_order(order1, sizeof(order1) / sizeof(int));
	jump_animation->set_ticks_per_frame(25);
	hit_animation = new Animated_texture(player_hit_texture, 4, -44, -28);
	int order2[] = { 0, 1, 2, 3, 1 };
	hit_animation->set_frame_order(order2, sizeof(order2) / sizeof(int));

	collision_box = { (int)pos_x, (int)pos_y, width, height };

	state = new E_Stand;
	state_stack.push(state);

	AI_states* ai_state;
	ai_state = new AI_move;
	ai_state_stack.push(ai_state);

	vel_x = -2;
}


void Enemy::move() {
	if (vel_x > 0) {
		flip_right = true;
	}
	else if (vel_x < 0) {
		flip_right = false;
	}
	Movable_object::move();
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
	ai_state_stack.top()->logic(*this);
	state_stack.top()->logic(*this);
	collision_box = { (int)pos_x, (int)pos_y, width, height };
};

void Enemy::render() {
	state_stack.top()->render(*this);

	//Hit box rectangle
	double scale = camera->get_scale();
	SDL_Rect renderQuad = { (pos_x - camera->get_x()) * camera->get_scale(), (pos_y - camera->get_y()) * camera->get_scale(), width * scale, height * scale };
	//Outline of rectangle of texture
	SDL_SetRenderDrawColor(main_renderer, 255, 50, 0, 100);
	SDL_RenderDrawRect(main_renderer, &renderQuad);

}

