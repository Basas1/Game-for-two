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
private:
	int round(float f);

	//Jump speed
	int jump_vel;
	double t;

	//Object's texture
	Animated_texture* walk_animation;

	int frame;
	//SDL_Rect gSpriteClips[8];
	SDL_Rect *gSpriteClips;

	SDL_Rect* currentClip;
	SDL_RendererFlip flip;

};

