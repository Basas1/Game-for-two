#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include <stack>
#include "Teleport_ball.h"

class Player_states;

class Player : public Movable_object {
public:
	Player(int x = 2000, int y = 1100, int control = 0 );
	~Player();

	
	int controller;
	SDL_JoystickID gamepad_id;
	SDL_GameController* gamepad;

	//Event handler
	void handle_events(SDL_Event& event);

	void logic();

	void render();

	bool vulnerable;

	bool kill();

	int get_x();
	int get_y();

	//Player state
	Player_states* state;

	//Jump speed
	double jump_vel;

	//Fireball cooldown
	int fireball_cooldown;
	int teleport_cooldown;
	int hit_cooldown;
	int unkill_cooldown;

	void reduce_cooldowns();

	//Object's textures
	Animated_texture* stand_animation;
	Animated_texture* run_animation;
	Animated_texture* jump_animation_rise;
	Animated_texture* jump_animation_fall;
	Animated_texture* jump_effect_animation1;
	Animated_texture* jump_effect_animation2;
	Animated_texture* hit_animation;
	Animated_texture* fireball_cast_animation1;
	Animated_texture* fireball_cast_animation2;
	Animated_texture* dive_animation;
	Animated_texture* dive_end_animation;
	Animated_texture* arrow;
	Animated_texture* mark;

	Animated_texture** player_textures[20];
	bool texture_color_toggled;
	void toggle_texture_color();
	Uint8 color_r;
	Uint8 color_g;
	Uint8 color_b;

	int skip;

	bool fireball_casting;

	Teleport_ball* t_ball;
	//void teleport_to_ball();

	std::stack<Player_states*> state_stack;

};
