#pragma once
#include <SDL.h>
#include "Enemy.h"

class Enemy_states {
public:
	enum states {
		STAND_STATE,
		RUN_STATE,
		FIRE_STATE,
		JUMP_STATE,
		HIT1_STATE,
	};
	virtual ~Enemy_states() {};
	void change_state(Enemy& p, int state);
	virtual void logic(Enemy& p) {};
	virtual void render(Enemy& p) {};

};

class E_On_ground : public Enemy_states {
public:
	E_On_ground() {};
	void logic(Enemy& p);
};

class E_Stand : public E_On_ground {
public:
	void logic(Enemy& p);
	void render(Enemy& p);

};

class E_Run : public E_On_ground {
public:
	void logic(Enemy& p);
	void render(Enemy& p);
};

class E_Jump : public Enemy_states {
public:
	void logic(Enemy& p);
	void render(Enemy& p);
};

class E_Hit1 : public Enemy_states {
	void logic(Enemy& p);
	void render(Enemy& p);
};

