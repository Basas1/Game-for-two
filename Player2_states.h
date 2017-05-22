#pragma once
#include <SDL.h>
#include "Player2.h"

class Player2_states {
public:
	enum states {
		STAND_STATE,
		RUN_STATE,
		FIRE_STATE,
		JUMP_STATE,
		HIT1_STATE,
	};
	void change_state(Player2& p, int state);
	virtual ~Player2_states() {};
	virtual void handle_events(Player2& p, SDL_Event& event);
	virtual void logic(Player2& p) {};
	virtual void render(Player2& p) {};
};

class P2_On_ground : public Player2_states {
public:
	P2_On_ground() {};
	void handle_events(Player2& p, SDL_Event& event);
	void logic(Player2& p);
};

class P2_Stand : public P2_On_ground {
public:
	void logic(Player2& p);
	void render(Player2& p);

};

class P2_Run : public P2_On_ground {
public:
	void logic(Player2& p);
	void render(Player2& p);
};

class P2_Jump : public Player2_states {
public:
	P2_Jump();
	void handle_events(Player2& p, SDL_Event& event);
	void logic(Player2& p);
	void render(Player2& p);
private:
	char jump_count;
};

class P2_Hit1 : public Player2_states {
	void logic(Player2& p);
	void render(Player2& p);
};

