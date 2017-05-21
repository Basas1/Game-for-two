#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include <stack>

class Enemy_states;
class AI_states;

class Enemy : public Movable_object {
public:
	Enemy();
	~Enemy();
	void handle_events(SDL_Event& event) {};
	void move();
	void logic();
	void render();

	int get_x();
	int get_y();

	Enemy_states* state;

	//Object's textures
	Animated_texture* stand_animation;
	Animated_texture* run_animation;
	Animated_texture* jump_animation;
	Animated_texture* hit_animation;

	std::stack<Enemy_states*> state_stack;
	std::stack<AI_states*> ai_state_stack;

};

