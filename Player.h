#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"
#include "Fireball.h"


class Player : public Movable_object {
public:
	Player();
	~Player();

	//Event handler
	void handle_events(SDL_Event& event);

	//Move method
	void move();

	//Render object
	void render();

	int get_x();
	int get_y();
private:
	int round(float f);

	//Jump speed
	int jump_vel;

	bool flip_left;
	Fireball* ball;

	//Object's texture
	Animated_texture* walk_animation;

	//point that camera follows
	int center_x, center_y;
};

