#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include <stack>

class Player_states;

class Player : public Movable_object {
public:
	Player();
	~Player();

	//Event handler
	void handle_events(SDL_Event& event);

	void logic();

	void render();

	int get_x();
	int get_y();

	//Player state
	Player_states* state;

	int round(float f);

	//Jump speed
	int jump_vel;

	//Object's textures
	Animated_texture* stand_animation;
	Animated_texture* run_animation;
	Animated_texture* jump_animation;
	Animated_texture* hit_animation;

	//point that camera follows
	int center_x, center_y;

	std::stack<Player_states*> state_stack;

};
