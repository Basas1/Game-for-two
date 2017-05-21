#pragma once
#include <SDL.h>
#include "Enemy.h"


class AI_states {
public:
	enum states {
		STAND_STATE,
		RUN_STATE,
		FIRE_STATE,
		JUMP_STATE,
		HIT1_STATE,
	};
	virtual ~AI_states() {};
	//void change_state(Enemy& p, int state);
	virtual void logic(Enemy& p) {};
};

class AI_move : public AI_states {
public:
	void logic(Enemy& p);
};


