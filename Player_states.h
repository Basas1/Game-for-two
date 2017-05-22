#pragma once
#include <SDL.h>
#include "Player.h"

class Player1_states {
public:
	enum states {
		STAND_STATE,
		RUN_STATE,
		FIRE_STATE,
		JUMP_STATE,
		HIT1_STATE,
	};
	void change_state(Player& p, int state);
	virtual ~Player1_states() {};
	virtual void handle_events(Player& p, SDL_Event& event);
	virtual void logic(Player& p) {};
	virtual void render(Player& p) {};
};

class On_ground : public Player1_states {
public:
	On_ground() {};
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
};

class Stand : public On_ground {
public:
	void logic(Player& p);
	void render(Player& p);

};

class Run : public On_ground {
public:
	void logic(Player& p);
	void render(Player& p);
};

class Jump : public Player1_states {
public:
	Jump();
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
	void render(Player& p);
private:
	char jump_count;
};

class Hit1 : public Player1_states {
	void logic(Player& p);
	void render(Player& p);
};

