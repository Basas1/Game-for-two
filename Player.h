#pragma once
#include "Movable_object.h"
#include "Animated_texture.h"


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

	int get_vision_x();
	int get_vision_y();
private:
	int round(float f);

	//Jump speed
	int jump_vel;

	//Object's texture
	Animated_texture* walk_animation;

	//point that camera follows
	int vision_focus_x, vision_focus_y;
};

