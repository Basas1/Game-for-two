#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"

class Teleport_ball : public Movable_object {
public:
	Teleport_ball(int x, int y, int side);
	~Teleport_ball();

	//Move method
	void move();

	void logic();

	//Render object
	void render();

	int create_time;
	bool stage_two;

	Animated_texture* teleport_ball_animation;
	int b_width, b_height;
};

