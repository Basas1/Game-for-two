#pragma once
#include <SDL.h>
#include <vector>

class Game_object {
public:
	enum object_types {
		PLAYER,
		ENEMY,
		FIREBALL,
		TELEPORT,
		OTHER,
		PLATFORM,
		HELP,
	};
	int type;

	Game_object();
	virtual void handle_events(SDL_Event& event) = 0;
	virtual void logic() = 0;
	virtual void render() = 0;

	//Check if object exist
	bool is_exist();
	virtual bool kill(int change = 0);

	bool collidable;
	//Collision box
	SDL_Rect collision_box;

	//Checks for collision with other game objects
	std::vector<Game_object*> get_collisions(SDL_Rect* check_box = NULL);

	//Check for collision between two collision boxes
	bool check_collision(SDL_Rect a, SDL_Rect b);

	//Object's coordinates
	double pos_x, pos_y;

	//Object's velocity
	double vel_x, vel_y;

	//Object constant acceleration in motion
	double acceleration;

	double score;
	bool on_platform;
	int time_on_platform;

	int skip;

	//Object size
	int width, height;

	Game_object* parent;

	//Flag of object existance
	bool exist;
};

