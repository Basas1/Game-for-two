#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Game_object.h"


class Movable_object : public Game_object {
public:
	Movable_object();

	//Move method
	void move();

	//Event handler
	void handle_events(SDL_Event& event);

	//Render object
	virtual void render() = 0;

	virtual ~Movable_object() {};

	//Check for collision with other objects
	bool check_collision();

	//Check for map collision in coordinate (x,y)
	bool check_map_collision(int x, int y);

	//Check bottom of object collision box for collision with map
	bool check_map_collision_bottom();

	bool check_map_collision_under();

	//Check upper of object collision box for collision with map
	bool check_map_collision_upper();

	//Check side of object collision box for collision with map
	bool check_map_collision_left();
	bool check_map_collision_right();

	//Check all collisions
	bool check_map_collision_all();

	//Object's coordinates
	double pos_x, pos_y;

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

	int can_rise;

	//True if object turn to rigrht side
	bool flip_right;

	//Object's texture
	Texture* texture;

	//Collision box
	SDL_Rect collision_box;
};

