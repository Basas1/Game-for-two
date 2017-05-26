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
	};
	int type;

	Game_object();
	virtual void handle_events(SDL_Event& event) = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Game_object() {};
	//Check if object exist

	bool is_exist();
	virtual bool kill();

	bool collidable;
	//Collision box
	SDL_Rect collision_box;

	//Checks for collision with other game objects
	std::vector<Game_object*> get_collisions(SDL_Rect* check_box = NULL);

	//Check for collision between two collision boxes
	bool check_collision(SDL_Rect a, SDL_Rect b);


	//Object's coordinates
	double pos_x, pos_y;

	//Object size
	int width, height;

protected:
	//Flag of object existance
	bool exist;
};

