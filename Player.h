#pragma once
#include "Movable_object.h"


class Player : public Movable_object {
public:
	Player();
	~Player();


	//Event handler
	void handle_events(SDL_Event& e);

	//Move method
	void move();

	//Render object
	void render();

};

