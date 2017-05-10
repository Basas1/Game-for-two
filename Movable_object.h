#pragma once
#include <SDL.h>
#include "Texture.h"


class Movable_object {
public:
	Movable_object();

	//Move method
	virtual void move() = 0;

	//Render object
	virtual void render() = 0;

	virtual ~Movable_object() {};

	//Return object's coordinate
	int get_x();
	int get_y();

protected:
	//Check for collision with other objects
	bool check_collision();

	//Object's coordinates
	int pos_x, pos_y;

	//Object size
	int width, height;

	//Object's velocity
	double vel_x, vel_y;

	//Max object's velocity
	int max_vel_x, max_vel_y;

	//Object's current acceleration
	double acc_x, acc_y;

	//Object constant acceleration in motion
	double acceleration;

	//Gravity
	double gravity;

	//Friction
	double friction;

	//Object's texture
	Texture* texture;

	//Collision box
	SDL_Rect collision_box;
};

