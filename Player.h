#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include <stack>
#include "Teleport_ball.h"

class Player1_states;

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
	Player1_states* state;

	//Jump speed
	int jump_vel;

	//Object's textures
	Animated_texture* stand_animation;
	Animated_texture* run_animation;
	Animated_texture* jump_animation;
	Animated_texture* hit_animation;
	Animated_texture* hit2_animation;

	Teleport_ball* t_ball;

	std::stack<Player1_states*> state_stack;

};
