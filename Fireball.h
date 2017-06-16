#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include "Static_object.h"


class Fireball : public Movable_object {
public:
	Fireball(int x, int y, int side, Player* p);

	//Move method
	void move();

	void logic();

	//Render object
	void render();

	void reverse();

	double get_angle();

	Player* player;

	Animated_texture* fireball_animation;
	Animated_texture* p1_fireball_animation;
	Animated_texture* p2_fireball_animation;

	Fireball_trail* last_trail;
	double angle;
};

