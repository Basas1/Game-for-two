#pragma once
#include <SDL.h>

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
	void kill();

	bool collidable;
	//Collision box
	SDL_Rect collision_box;

	//Object's coordinates
	double pos_x, pos_y;

	//Object size
	int width, height;

protected:
	//Flag of object existance
	bool exist;
};

