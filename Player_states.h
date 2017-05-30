#pragma once
#include <SDL.h>
#include "Player.h"

class Player_states {
public:
	enum states {
		STAND_STATE,
		RUN_STATE,
		FIRE_STATE,
		JUMP_STATE,
		HIT1_STATE,
		HIT2_STATE,
	};
	void change_state(Player& p, int state, int arg=0);
	void cast_fireball(Player& p);
	void cast_teleport_ball(Player& p);
	void blast_teleport_ball(Player& p);
	virtual ~Player_states() {};
	virtual void handle_events(Player& p, SDL_Event& event);
	virtual void logic(Player& p) {};
	virtual void render(Player& p) {};
};

class On_ground : public Player_states {
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

class Jump : public Player_states {
public:
	Jump(Player& p);
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
	void render(Player& p);
	char jump_count;
	bool falling;
};

class Hit1 : public Player_states {
public:
	void logic(Player& p);
	void render(Player& p);
};

class Hit2 : public Player_states {
public:
	Hit2(int jump);
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
	void render(Player& p);
	bool can_cancel;
};
