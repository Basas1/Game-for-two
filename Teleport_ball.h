#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"

class Player;
class Tp_ball_trail;

class Teleport_ball : public Movable_object {
public:
	Teleport_ball(int x, int y, Player* p, int side);
	~Teleport_ball();

	//Move method
	void move();

	void logic();

	//Render object
	void render();

	void blast();

	int create_time;
	bool stage_two;

	Animated_texture* teleport_ball_opening;
	Animated_texture* teleport_ball_opened;
	int blast_rad;
	int b_width, b_height;
	Tp_ball_trail* last_trail;
	Player* parent;
};

