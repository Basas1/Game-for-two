#pragma once
#include "Player.h"
#include <stack>


class Player2_states;

class Player2 :
	public Player {
public:
	Player2();
	~Player2();

	//Event handler
	void handle_events(SDL_Event& event);

	void logic();

	void render();


	Player2_states* state;

	std::stack<Player2_states*> state_stack;
};

