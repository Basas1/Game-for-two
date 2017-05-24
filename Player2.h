#pragma once
#include "Player.h"


class Player2 : public Player {
public:
	Player2(int x = 2100, int y = 1100, int controller = 0);
	~Player2();

	void kill();
};

