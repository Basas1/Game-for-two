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
	};
	void change_state(Player& p, int state);
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
	Jump();
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
	void render(Player& p);
private:
	char jump_count;
};

class Hit1 : public Player_states {
	void logic(Player& p);
	void render(Player& p);
};

