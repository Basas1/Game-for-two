#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include "Static_object.h"


class Fireball : public Movable_object {
public:
	Fireball(int x, int y, int side, Game_object* p);
	~Fireball();

	//Move method
	void move();

	void logic();

	//Render object
	void render();

	void reverse();

	Animated_texture* fireball_animation;

	Fireball_trail* last_trail;

};

