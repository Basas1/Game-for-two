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
		TELEPORTATION_STATE,
	};
	void change_state(Player& p, int state, int arg=0);
	void cast_fireball(Player& p);
	void create_fireball(Player& p, int side);
	void cast_teleport_ball(Player& p);
	void blast_teleport_ball(Player& p);
	std::tuple<double, double> teleport_to_ball(Player& p);
	virtual ~Player_states() {};
	virtual void handle_events(Player& p, SDL_Event& event);
	virtual void logic(Player& p) {};
	virtual void render(Player& p) {};
	int type;
};

class On_ground : public Player_states {
public:
	On_ground() { type = -1; };
	void handle_events(Player& p, SDL_Event& event);
	void logic(Player& p);
};

class Stand : public On_ground {
public:
	Stand() { type = STAND_STATE; };
	void logic(Player& p);
	void render(Player& p);

};

class Run : public On_ground {
public:
	Run() { type = RUN_STATE; };
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
	Hit1() { type = HIT1_STATE; };
	void handle_events(Player& p, SDL_Event& event) {};
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
	bool landing;
};

class Teleportation : public Player_states {
public:
	Teleportation(Player& p);
	void handle_events(Player& p, SDL_Event& event) {};
	void logic(Player& p);
	void render(Player& p);
	double start_x, start_y;
	double dest_x, dest_y;
	double v_x, v_y;
};
