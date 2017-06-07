#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Game_object.h"
#include <vector>



class Movable_object : public Game_object {
public:
	Movable_object();

	virtual ~Movable_object() {};

	void handle_events(SDL_Event& event) {};

	//Move method
	bool move();

	////Checks for collision with other game objects
	//std::vector<Game_object*> get_collisions(SDL_Rect* check_box=NULL);

	////Check for collision between two collision boxes
	//bool check_collision(SDL_Rect a, SDL_Rect b);

	//Check for map collision in coordinate (x,y)
	bool check_map_collision(int x, int y);

	//Check bottom of object collision box for collision with map
	bool check_map_collision_bottom();

	bool check_map_collision_under();

	//Check upper of object collision box for collision with map
	bool check_map_collision_upper();

	//Check side of object collision box for collision with map
	bool check_map_collision_left();
	bool check_map_collision_left_strict();
	bool check_map_collision_right();
	bool check_map_collision_right_strict();

	//Check all collisions
	bool check_map_collision_all();

	//Check if object can go to the side without stomping into something or falling
	bool can_go_left();
	bool can_go_right();

	//Max object's velocity
	int max_vel_x, max_vel_y;

	//Object's current acceleration
	double acc_x, acc_y;

	//Gravity
	double gravity;

	//Friction
	double friction;

	int can_rise;

	//True if object turn to rigrht side
	bool flip_right;

	//Object's texture
	Texture* texture;
};

