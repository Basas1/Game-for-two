#include <SDL.h>
#pragma once
class Programm_state {
public:
	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Programm_state() {};
};

void set_next_state(int new_state);
void change_state();
