#include <SDL.h>
#pragma once
class Programm_state {
public:
	enum prog_states {
		STATE_NULL,
		STATE_MENU,
		STATE_GAME,
		STATE_EXIT,
		STATE_PAUSE,
	};
	int state;

	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Programm_state() {};
};


class Exit_state : public Programm_state {
public:
	Exit_state();
	void handle_events() {};
	void logic() {};
	void render() {};
	~Exit_state() {};
};


void set_next_state(int new_state);
void change_state();
