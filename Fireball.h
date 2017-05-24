#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"

class Fireball : public Movable_object {
public:
	Fireball(int x, int y, int side);
	~Fireball();

	//Move method
	void move();

	void logic();

	//Render object
	void render();

	Animated_texture* fireball_animation;

};

